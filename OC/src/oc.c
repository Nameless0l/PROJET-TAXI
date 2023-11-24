#include <sys/ipc.h>
#include <sys/shm.h>

#include "../include/oc.h"
#include "../include/deque.h"
#include "../include/shared.h"
#include "../include/defines.h"
#include "../include/handlers.h"

/**
 * @brief init clients deque and bikes deque
 *
 */
void init_deques()
{
    bikes_deque = create_deque();
    clients_deque = create_deque();
    return;
}


/**
 * @brief init signals handlers for catched signal by OC
 *
 */
void init_sig_handlers()
{
    // client created
    struct sigaction client_sig;
    client_sig.sa_sigaction = handle_client_create;
    client_sig.sa_flags = SA_SIGINFO;

    sigemptyset(&client_sig.sa_mask);
    sigaction(CLIENT_CREATED, &client_sig, NULL);

    // bike created
    struct sigaction bike_sig;
    bike_sig.sa_sigaction = handle_bike_create;
    bike_sig.sa_flags = SA_SIGINFO;
    
    sigemptyset(&bike_sig.sa_mask);
    sigaction(BIKE_CREATED, &bike_sig, NULL);

    // client gone
    struct sigaction client_gone_sig;
    client_gone_sig.sa_sigaction = handle_client_gone;
    client_gone_sig.sa_flags = SA_SIGINFO;
    
    sigemptyset(&client_gone_sig.sa_mask);
    sigaction(CLIENT_GONE, &client_gone_sig, NULL);
    //*/
}

void init_oc()
{
    printf("==========Starting Central Scheduling===========\n\n");
    printf("Initialising deque . . . ");
    init_deques();
    printf("ok \n");
    printf("Initialising signals handlers . . . ");
    init_sig_handlers();
    printf("ok \n\n");
    return;
}

/**
 * @brief proper when killing oc
 *
 */
void end_oc()
{
    if (bikes_deque != NULL)
        destroy_deque(bikes_deque);
    
    if (clients_deque != NULL)
        destroy_deque(clients_deque);
}

/**
 * @brief get shared memory created by client or bike process
 *
 * @param pid(pid_t) pid
 * @return void*
 */
void *get_shm(pid_t pid)
{
    key_t shared_key = pid;
    int shmid = shmget(shared_key, SEG_SIZE, 0666 | IPC_CREAT);
    void *ret = shmat(shmid, NULL, 0);

    if (ret == ((void *)-1))
        fprintf(stderr, "cannot acess shared memory\n");
    else
        return ret;
}

/**
 * @brief run the scheduler
 *
 */
void schedule()
{
    printf("\nStarting scheduling routine . . .\n");
    printf("temporary masking creation signals reception . . .\n\n");
    fflush(stdout);


    // blocking clients create, bikes create and clients gone signal
    struct sigaction new_sigaction;
    sigset_t new_sig_set;

    // setting blocking signals
    sigemptyset(&new_sig_set);
    sigaddset(&new_sig_set, CLIENT_CREATED);
    sigaddset(&new_sig_set, CLIENT_GONE);
    sigaddset(&new_sig_set, BIKE_CREATED);

    // blocking
    sigprocmask(SIG_BLOCK, &new_sig_set, NULL);

    printf("scheduling . . .\n");
    /* Starting scheduling */

    printf("All bikes in deque : [");
    block* currentt_bike = bikes_deque->start;
    while(currentt_bike != NULL)
    {
        printf("%d,", currentt_bike->pid);
        currentt_bike = currentt_bike->next;
    }
    printf("]\n"); fflush(stdout); //*/

    printf("All clients in the deque : [");
    fflush(stdout);
    block* currentt_client = clients_deque->start;
    while(currentt_client != NULL)
    {
        printf("%d,", currentt_client->pid);
        currentt_client = currentt_client->next;
    }
    printf("]\n"); fflush(stdout);


    deque *deque_bikes_states = create_deque();
    block* currenttt_bike = bikes_deque->start;
    while(currenttt_bike != NULL)
    {
        push_back(deque_bikes_states, _free);
        currenttt_bike = currenttt_bike->next;
    }

    deque* bikes_to_delete = create_deque();
    deque* clients_to_delete = create_deque();
    block* current_client = clients_deque->start;

    while(current_client != NULL)
    {
        bool bike_found = false;
        Client *client_infos = (Client *)get_shm(current_client->pid);;

        block *current_bike = bikes_deque->start;
        block *current_bike_state = deque_bikes_states->start;
        while(current_bike != NULL && current_bike_state != NULL)
        {
            if (current_bike_state->pid == _taken)
                continue;

            Bike *bike_infos = (Bike*)get_shm(current_bike->pid);
            for (int i = 0; i < RADIUS; ++i)
            {
                if (bike_infos->itinerary[i] == client_infos->dest)
                {
                    bike_found = true;
                    break;
                }
            }

            if (bike_found)
            {
                pid_t* p1 = (pid_t*)bike_infos;
                *p1 = current_client->pid;

                pid_t* p2 = (pid_t*)client_infos;
                *p2 = current_bike->pid;

                push_back(bikes_to_delete, current_client->pid);
                push_back(clients_to_delete, current_client->pid);

                kill(current_client->pid, BIKE_ASSIGNED);
                kill(current_bike->pid, CLIENT_ASSIGNED);

                current_bike_state->pid = _taken;
                break;
            }

            current_bike = current_bike->next;
            current_bike_state = current_bike_state->next;
        }

        current_client = current_client->next;
    }

    block* bike_to_delete = bikes_to_delete->start;
    while(bike_to_delete != NULL)
    {
        delete_block(bikes_deque, bike_to_delete->pid);
        bike_to_delete = bike_to_delete->next;
    }

    block* client_to_delete = clients_to_delete->start;
    while(client_to_delete != NULL)
    {
        delete_block(clients_deque, client_to_delete->pid);
        client_to_delete = client_to_delete->next;
    }

    printf("End of scheduling . . .\n");
    printf("unmasking signals sent inside scheduling. . .\n");
    fflush(stdout);

    // unblock signals
    sigprocmask(SIG_UNBLOCK, &new_sig_set, NULL);
    // */
    printf("End of scheduling routine\n");
    fflush(stdout);
}
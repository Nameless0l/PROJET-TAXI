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

    sigaction(CLIENT_CREATED, &client_sig, NULL);

    // client gone
    struct sigaction client_gone_sig;
    client_gone_sig.sa_sigaction = handle_client_gone;
    client_gone_sig.sa_flags = SA_SIGINFO;

    sigaction(CLIENT_GONE, &client_gone_sig, NULL);

    // bike created
    struct sigaction bike_sig;
    bike_sig.sa_sigaction = handle_bike_create;
    bike_sig.sa_flags = SA_SIGINFO;

    sigaction(BIKE_CREATED, &bike_sig, NULL);
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
    destroy_deque(bikes_deque);
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
    int shmid = shmget(shared_key, 1024, 0666 | IPC_CREAT);
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
    sleep(10);
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
    fflush(stdout);
    /* Starting scheduling */

    printf("clients in deque : [");
    for (block *current_client = clients_deque->start; current_client != NULL; current_client = current_client->next)
        printf("%d,", current_client->pid);
    printf("]\n");

    printf("Bikes in deque : [");
    for (block *current_bike = bikes_deque->start; current_bike != NULL; current_bike = current_bike->next)
        printf("%d,", current_bike->pid);
    printf("]\n");

    for (block *current_client = clients_deque->start; current_client != NULL; current_client = current_client->next)
    {
        void *client_ptr = get_shm(current_client->pid);
        Client *c = (Client *)client_ptr;
        
        for (block *current_bike = bikes_deque->start; current_bike != NULL; current_bike = current_bike->next)
        {
            void *bike_ptr = get_shm(current_bike->pid);
            Bike *b = (Bike*)bike_ptr;

            printf("Infos : (dest = %d)\n", c->dest);
            printf("Infos : (it = %d)\n", b->itinerary[0]);

            fflush(stdout);
            exit(1);

            for (int i = 0; i < RADIUS; ++i)
            {
                if (b->itinerary[i] == c->dest)
                {
                    printf("adsz\n");
                    pid_t *p1 = (pid_t *)bike_ptr;
                    *p1 = current_client->pid;
                    printf("yo\n");

                    pid_t *p2 = (pid_t *)client_ptr;
                    *p2 = current_bike->pid;
                    printf("ici\n");

                    kill(current_client->pid, BIKE_ASSIGNED);
                    kill(current_bike->pid, CLIENT_ASSIGNED);

                    //delete_block(clients_deque, current_bike->pid);
                    printf("ici2");
                    //delete_block(bikes_deque, current_client->pid);
                    printf("lala");
                    break;
                }
            }
            delete_block(clients_deque, current_client->pid);
            delete_block(bikes_deque, current_bike->pid);
        }
    }

    printf("End of scheduling . . .\n");
    printf("unmasking signals sent inside scheduling. . .\n");
    fflush(stdout);
    // unblock signals
    sigprocmask(SIG_UNBLOCK, &new_sig_set, NULL);

    printf("End of scheduling routine\n");
    fflush(stdout);
}
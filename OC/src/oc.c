#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "../include/oc.h"
#include "../include/list.h"
#include "../include/shared.h"
#include "../include/defines.h"
#include "../include/handlers.h"
#include "../include/gData_list.h"

void oc_log(List *bikes_list, List *clients_list){
    system("clear");

    int n_bikes = count_list_values(bikes_list);
    int n_clients = count_list_values(clients_list);
    int n_max = n_bikes > n_clients ? n_bikes : n_clients;

    Block *cur_bike = bikes_list->start;
    Block *cur_client = clients_list->start;

    printf("\n\nSCHEDULING LOG...\n");
    printf("%10s | %10s\n", "Bikes", "Clients");

    for(int i = 0; i < n_max; i++){
        if(cur_bike){
            printf("%10d |", cur_bike->pid);
            cur_bike = cur_bike->next;
        }else{
            printf("%10s |", "");
        }

        if(cur_client){
            printf("%10d |", cur_client->pid);
            cur_client = cur_client->next;
        }else{
            printf("%10s |", "");
        }

        printf("\n");
    }

    printf("\n");
    fflush(stdout);
}

/**ù
 * @brief run the scheduler
 */
void schedule(pid_t ui_pid)
{
    // Blocking clients create, bikes create and clients gone signal
    struct sigaction new_sigaction;
    sigset_t new_sig_set;

    set_blocking_signals(&new_sig_set);

    oc_log(bikes_list, clients_list);

    // Will contain clients and lists that has been assigned
    List* assigned_bikes = create_list();
    List* assigned_clients = create_list();

    int bikes_count = count_list_values(bikes_list);
    bool* bikes_states = (bool*)malloc(sizeof(bool) * bikes_count);
    for(int i = 0; i < bikes_count; ++i)
        bikes_states[i] = _free;

    /* for each client, search for the first **free** bike that itinerary matches  */
    Block* current_client = clients_list->start;

    while(current_client != NULL)
    {
        // Access client segment and get info. if it doesn't exists, delete client in clients_list
        if (!check_shm_exist(current_client->pid))
        {
            Block* client_gone = current_client;
            current_client = current_client->next;
            delete_block(clients_list, client_gone->pid);
            
            continue;
        }
        
        Client* client_infos = (Client*)get_shm(current_client->pid);

        // Iterating over bikes
        bool bike_found = false;
        int bikes_states_iter = 0;
        
        Block* current_bike = bikes_list->start;

        while (current_bike)
        {
            if (bikes_states[bikes_states_iter] == _taken) // Bike already taken, pass
            {
                ++bikes_states_iter;
                current_bike = current_bike->next;
                
                continue;
            }

            // acess bike segment info. if it doesn't exists, delete bike form bikes_list
            if (!check_shm_exist(current_bike->pid))
            {
                Block* bike_to_delete = current_bike;
                current_bike = current_client->next;
                delete_block(bikes_list, bike_to_delete->pid);

                continue;
            }

            Bike *bike_infos = (Bike*)get_shm(current_bike->pid);

            // Search for the client destination in the bike intinerary
            if(bike_founded(bike_infos, client_infos)){
                pid_t bike_pid = current_bike->pid;
                pid_t client_pid = current_client->pid;

                bike_found = true;
                printf("\t> Corresponding Found (Bike(pid=%d), Client(pid=%d))\n", bike_pid, client_pid);

                appendGData(corresponding_gDatas, bike_pid, bike_infos->start, client_pid, client_infos->start, client_infos->dest);

                // adding to assigned bikes and clients
                push_back(assigned_bikes, bike_pid);
                push_back(assigned_clients, client_pid);

                // sending signals to client and bike
                kill(client_pid, BIKE_ASSIGNED);
                kill(bike_pid, CLIENT_ASSIGNED);

                // marking actual bike as free
                bikes_states[bikes_states_iter] = _taken;
                break;
            }

            current_bike = current_bike->next;
            ++bikes_states_iter;
        }

        current_client = current_client->next;
    }

    write_structures_in_ui_shm(corresponding_gDatas, ui_pid);

    delete_assigned(bikes_list, assigned_bikes);
    delete_assigned(clients_list, assigned_clients);
    destroy_list(assigned_bikes);
    destroy_list(assigned_clients);

    free(bikes_states);

    // unblock signals
    sigprocmask(SIG_UNBLOCK, &new_sig_set, NULL);
}

void write_structures_in_ui_shm(HeadGData *corresponding_gDatas, pid_t ui_pid){
    int can_write = ((int*)ui_shm)[0] == 0;

    if (can_write){
        void *ui_shm_ptr = ui_shm + 2 * sizeof(int);

        // Writing graphic data structures
        GData *cur_data = corresponding_gDatas->first;

        while(cur_data){
            memcpy(ui_shm_ptr, cur_data, sizeof(GData));

            ui_shm_ptr += sizeof(GData);
            cur_data = cur_data->next;
        }

        ((int*)ui_shm)[1] = corresponding_gDatas->n;
        ((int*)ui_shm)[0] = 1;

        //kill(ui_pid, UI_SIGNAL);
        clear_gDatas(corresponding_gDatas);
    }
}

// deleting assigned clients and bikes from lists
void delete_assigned(List *list, List *assigned)
{
    Block* to_delete = assigned->start;
    
    while(to_delete)
    {
        delete_block(list, to_delete->pid);
        to_delete = to_delete->next;
    }
}

/**
 * @brief init clients list and bikes list
 */
void my_sleep()
{
    for (int i = 0; i < 0xffffffff; ++i);
}

void init_lists()
{
    bikes_list = create_list();
    clients_list = create_list();

    return;
}

void init_oc()
{
    printf("========== STARTING CENTRAL SCHEDULING ===========\n\n");
    
    printf("> Initialising list... ");
    init_lists();
    printf("OK\n");
    
    printf("> Initialising signals handlers... ");
    init_sig_handlers();
    printf("OK\n\n");
    
    return;
}

/**
 * @brief proper when killing oc
 *
 */
void end_oc(pid_t ui_pid)
{
    if (bikes_list != NULL)
        destroy_list(bikes_list);
    
    if (clients_list != NULL)
        destroy_list(clients_list);

    int shmid = shmget((key_t)ui_pid, UI_SEG_SIZE, IPC_CREAT | IPC_EXCL);
    shmctl(shmid, IPC_RMID, NULL);
}


/**
 * @brief check if a shared memory segment exist
 * 
 * @param pid the key of the segment
 * @return true if the segment exist
 * @return false otherwise
 */
bool check_shm_exist(pid_t pid)
{
    errno = 0;
    int shmid = 0;
    key_t shared_key = pid;
    if ((shmid = shmget(shared_key, SEG_SIZE, IPC_CREAT | IPC_EXCL)) == -1)
    {
        if (errno == EEXIST) // segment exist
            return true;
        else
            return false;
    }

    shmctl(shmid, IPC_RMID, NULL);
    return false;
}

// Create shared memory
void create_ui_memory()
{
    // create shared memory for client
    int shm_id = shmget((key_t)getpid(), UI_SEG_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1)
    {
        perror("Failed to create a shared memory");
        exit(EXIT_FAILURE);
    }

    // Attach physical memory to virtual shared memory
    ui_shm = shmat(shm_id, NULL, 0);
    if (ui_shm == (void *)-1)
    {
        perror("Failed to attach a physic memory to the virtual chared memory created among"); // print error message if it failed
        exit(EXIT_FAILURE);
    }

    ((int*)ui_shm)[0] = 0;
}

void set_blocking_signals(sigset_t *new_sig_set)
{
    // Setting blocking signals
    sigemptyset(new_sig_set);
    sigaddset(new_sig_set, CLIENT_CREATED);
    sigaddset(new_sig_set, CLIENT_GONE);
    sigaddset(new_sig_set, BIKE_CREATED);

    // blocking
    sigprocmask(SIG_BLOCK, new_sig_set, NULL);
}

bool bike_founded(Bike *bike, Client *client){
    for(int i = 0; i < RADIUS; ++i)
        if(bike->itinerary[i] == client->dest)
            return true;
}

/**
 * @brief get shared memory created by client or bike process
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
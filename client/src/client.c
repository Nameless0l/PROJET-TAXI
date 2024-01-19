#include "../include/defines.h"
#include "../include/client.h"

// Set handlers for signals
void set_handlers()
{
    signal(BIKE_ASSIGNED, &client_handler);
    signal(STARTED_COURSE, &client_handler);
    signal(ENDED_COURSE, &client_handler);
}

// The client wait until the bike finish his task
void client_wait(int n)
{
    if (!n)
    {
        while (1)
            sleep(TASK_TIME);
    }
    else
    {
        sleep(n);
    }
}

// Client handler
void client_handler(int sig)
{
    switch (sig)
    {
    case BIKE_ASSIGNED:
        break;
    case STARTED_COURSE:
        client_wait(0);
        break;
    case ENDED_COURSE:
        break;
    default:
        break;
    }
}

// Generate client's parameters
Client *generate_client()
{
    Client *new_client = (Client *)malloc(sizeof(Client));

    // If allocation failed
    if (!new_client)
        return NULL;

    // Filling client's parameters
    new_client->start = (Quarter)random_integer(0, NB_QUARTER);
    new_client->dest = (Quarter)random_integer(0, NB_QUARTER); // This modulo is used to be sure that the integer which will show the des in enumeration is not aut of range
    new_client->wait_time = random_integer(MIN_WAIT_TIME, MAX_WAIT_TIME + 1);
    new_client->pid = getpid();

    return new_client;
}

// Return a random integer between a and b excluded
int random_integer(int a, int b)
{
    return (rand() % (b - a - 1)) + a;
}

// Create shared memory
void create_memory(pid_t client_pid)
{
    // create shared memory for client
    int shm_id = shmget((key_t)client_pid, SEG_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1)
    {
        perror("Failed to create a shared memory");
        exit(EXIT_FAILURE);
    }

    // Attach physical memory to virtual shared memory
    shared_mem = shmat(shm_id, NULL, 0);
    if (shared_mem == (void *)-1)
    {
        perror("Failed to attach a physic memory to the virtual chared memory created among"); // print error message if it failed
        exit(EXIT_FAILURE);
    }
}

void write_client_infos(Client *client)
{
    memcpy(shared_mem, client, sizeof(Client));

    kill(oc_pid, CREATED_CLIENT);
}

void free_shm(pid_t client_pid)
{
    int shm_id = shmget((key_t)client_pid, SEG_SIZE, IPC_CREAT | 0666);
    shmctl(shm_id, IPC_RMID, NULL);
}

//print informations of a client
void print_client(Client *client)
{
    printf("> Client(pid=%d, start=%d, dest=%d, price=%d, wait_time=%ld)\n", client->pid, client->start, client->dest, client->price, client->wait_time);
}

//print informations written on the shared memory
void print_client_segment()
{
    Client *client = (Client *)shared_mem;

    print_client(client);
}

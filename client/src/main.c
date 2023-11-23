#include "../include/defines.h"
#include "../include/client.h"

pid_t oc_pid;
void *shared_mem;

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    // Get CS's pid
    oc_pid = atoi(argv[1]);

    // Set handler
    set_handlers();

    // Create a new client
    Client *client = generate_client();

    printf("CLIENT INFOS\t");
    print_client(client);

    // Create shared memory
    create_memory(client->pid);

    // Write client's infos in the shared memory
    write_client_infos(client);

    printf("SHM CONTENT\t");
    print_client_segment();

    client_wait(CLIENT_WAIT_TIME);

    //Here we have to add a kill to the Central Scheduler to say that we have wait enough
    kill(oc_pid, CLIENT_GONE);

    // Freeing the client and shm
    free_shm(client->pid);
    free(client);

    return EXIT_SUCCESS;
}

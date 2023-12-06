#include "../include/ui.h"
#include "../include/defines.h"

#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "../include/handler.h"

void init_handlers()
{
    struct sigaction oc_sig;
    oc_sig.sa_sigaction = handle_oc_scheduled;
    oc_sig.sa_flags = SA_SIGINFO;

    sigemptyset(&oc_sig.sa_mask);
    sigaction(OC_HAS_SCHEDULED, &oc_sig, NULL);
}


void handle_oc_scheduled(int signum, siginfo_t *info, void *context)
{
    if(signum == OC_HAS_SCHEDULED)
    {
        // access the oc shm
        key_t shared_key = info->si_pid;
        int shmid = shmget(shared_key, OC_SHM_SIZE, 0);
        if (shmid == -1)
        {
            write(1, "error, cannot access shared memory of the OC !\n", 47);
            exit(-1);
        }
    
        void *oc_shm = shmat(shmid, NULL, 0);
        void *oc_shm_start = oc_shm;

        bool can_read_shm = (((int*)oc_shm)[0] == 1);
        if (can_read_shm)
        {
            int nb_pairs = ((int*)oc_shm)[1];
            oc_shm += 2 * sizeof(int);

            for (int i = 0; i < nb_pairs; ++i)
            {
                G_data* datas = (G_data*)oc_shm;

                G_client* client = (G_client*)malloc(sizeof(*client));
                Point *client_dest = get_quater_pos(datas->client_dest);
                Point *client_start = get_quater_pos(datas->client_start);
                Point *client_center = get_quater_pos(datas->client_start);
                client->dest = client_dest;
                client->start = client_start;
                client->radius = _RADIUS;
                client->center = client_center;

                G_bike* bike = (G_bike*)malloc(sizeof(*bike));
                Point *bike_start = get_quater_pos(datas->bike_start);
                Point *bike_center = get_quater_pos(datas->bike_start);
                bike->side = _SIDE;
                bike->center = bike_center;
                bike->start = bike_start;

                push_front(bikes_n_clients_list, datas->bike_pid, datas->client_pid, bike, client);

                // mark the shm validity bit at 0
                ((int*)oc_shm_start)[0] = 0;
                oc_shm += sizeof(G_data);
            }

            write(1, "abc", 3);
        }
        else
        {
            write(1, "error, cannot read the shared memory segment of the oc !\n", 47);
            exit(-1);   
        }
    }
    else
        write(1, "incorrect signal sent !\n", 24);
}
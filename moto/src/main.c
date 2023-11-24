#include <time.h>
#include "../include/defines.h"
#include "../include/signal.h"
#include "../include/initialisation_bikes.h"

Bike *bike;
pid_t oc_pid;
int shm_id;	// id of area
void *shm_zone;	//attach area
key_t shm_key;	// clief of area

void print_bike(Bike *bike)
{
    printf("Bike(pid = %d, Itinerary = [", bike->pid);
    
    for(int i = 0; i < RADIUS; i++)
        printf("%s, ", quartier[bike->itinerary[i]]);
    printf("]\n");
}

void print_segment(){
    Bike *bike = (Bike*)shm_zone;

    print_bike(bike);
}

/* a variable which content things that we want to write to shm the first argument(argv[1]) content the clief of shm and the oder content the things that we want to write in the shm argc content the numbers of arguments argv must have at least 2 arguments */
int main(int argc,char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Error, you should specify the oc pid as argument\n");
        return -1;
    }
    
    // initialisation du générateur aléatoire . . .
    srand(time(NULL));

    set_handler();

    // Create a new bike
    bike = create_bike();

    // Test
    print_bike(bike);
    
    // Create bike's associated segmente
    create_segment(bike->pid);

    // Write bike's infos in the shared segment
    write_infos_bike(bike);

    // Test
    print_segment();

    // Get the central scheduler pid
    oc_pid = atoi(argv[1]);

    // Send the signal to the CS
    send_signal(oc_pid, BIKE_CREATED);

    // W
    while(true)
        sleep(WAIT_TIME);
    
    shmctl(shm_id, IPC_RMID, NULL);
    free(bike);
    
   	return EXIT_SUCCESS;
 }
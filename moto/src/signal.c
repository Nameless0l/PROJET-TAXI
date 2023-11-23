#include "../include/defines.h"
#include "../include/signal.h"
#include "../include/initialisation_bikes.h"

// Generate a random integer between a and b included
int random_integer(int a, int b)
{
	return (rand() % (b - a + 1)) + a;
}

int starting_course(pid_t client_pid)
{
	return !kill(client_pid, STARTED_COURSE);
}

void ended_course(pid_t client_pid)
{
	kill(client_pid, ENDED_COURSE);
}

// Receive a signal of client and read in the shm the pid of client and change a statut of moto
void bike_handler(int signum)
{
	if (signum != SEGMENT_READY)
		return;

	pid_t client_pid = *((pid_t *)shm_zone);

	// Send a signal to precise that we are carrying a client
	if (starting_course(client_pid))
	{
		// Time interfal for the course
		sleep(random_integer(TASK_TIME_MIN, TASK_TIME_MAX));

		// Send a signal to precise that we have ended the course
		ended_course(client_pid);
	}

	// Write again bike's infos
	write_infos_bike(bike);

	// Resend the signal to the CS
	send_signal(oc_pid, BIKE_CREATED);
}

// Atttach functions to signal
void set_handler()
{
	signal(SEGMENT_READY, &bike_handler);
}

// Send signal to CS
void send_signal(pid_t oc_pid, int sig)
{
	kill(oc_pid, sig);
}

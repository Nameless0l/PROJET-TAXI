#include <stdio.h>

#include "../include/oc.h"
#include "../include/handlers.h"

/**
 * @brief handler for client creation signal
 * 
 * @param signum(int) id of the signal
 * @param info(siginfo_t*) signal sender info
 * @param context(void*) signal sender context 
 */
void handle_client_create(int signum, siginfo_t *info, void *context)
{
    if (signum == CLIENT_CREATED)
    {
        push_back(clients_deque, (pid_t)info->si_pid);
        printf("process with pid %d has been inserted in the clients list\n", (pid_t)info->si_pid);
        fflush(stdout);
        return;
    }
    else
        fprintf(stderr, "incorrect signal sent !\n");
}


/**
 * @brief handle for client gone signal
 * 
 * @param signum(int) id of the signal
 * @param info(siginfo_t*) signal sender info
 * @param context(void*) signal sender context 
 */
void handle_client_gone(int signum, siginfo_t* info, void* context)
{
    if (signum == CLIENT_GONE)
    {
        delete_block(clients_deque, (pid_t)info->si_pid);
        printf("process with pid %d has been removed in the clients list\n", (pid_t)info->si_pid);
        fflush(stdout);
        return;
    }
    else
        fprintf(stderr, "incorrect signal sent !\n");
}


/**
 * @brief handler for bike creation signal
 * 
 * @param signum(int) id of the signal
 * @param info(siginfo_t*) signal sender info
 * @param context(void*) signal sender context 
 */
void handle_bike_create(int signum, siginfo_t *info, void *context)
{
    if (signum == BIKE_CREATED)
    {
        push_back(bikes_deque, (pid_t)info->si_pid);
        printf("process with pid %d has been inserted in the bikes list\n", (pid_t)info->si_pid);
        fflush(stdout);
        return;
    }
    else
        fprintf(stderr, "incorrect signal sent !\n");
}
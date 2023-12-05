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
        char buf[BUF_SIZE] = "";

        pid_t pid = (pid_t)info->si_pid;
        sprintf(buf, "> Client inserted : PID(%d)\n", pid);

        push_back(clients_list, (pid_t)info->si_pid);
        write(1, buf, strlen(buf));

        return;
    }
    else
        write(1, "incorrect signal sent !\n", 24);
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
        char buf[BUF_SIZE] = "";

        pid_t pid = (pid_t)info->si_pid;
        sprintf(buf, "> Client gone : PID(%d)\n", pid);

        delete_block(clients_list, pid);
        write(1, buf, strlen(buf));
        
        return;
    }
    else
        write(1, "incorrect signal sent !\n", 24);
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
        char buf[BUF_SIZE] = "";
        
        pid_t pid = (pid_t)info->si_pid;
        sprintf(buf, "> Bike inserted : PID(%d)\n", pid);

        push_back(bikes_list, pid);
        write(1, buf, strlen(buf));

        return;
    }
    else
        write(1, "incorrect signal sent !\n", 24);
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
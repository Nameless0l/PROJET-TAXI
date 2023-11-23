#include "../include/oc.h"
#include "../include/deque.h"
#include "../include/defines.h"

#include <unistd.h>
#include <stdio.h>

deque *bikes_deque;
deque *clients_deque;

int main()
{
    init_oc();
    printf("PID of the Central Scheduler : %d\n", getpid());
    fflush(stdout); 

    while(1)
    {
        sleep(WAIT_UNTIL_SCHEDULE);
        schedule();
    } // */

    end_oc();
    return 0;
}
#include "../include/oc.h"
#include "../include/deque.h"
#include "../include/defines.h"

#include <unistd.h>
#include <stdio.h>

deque *bikes_deque;
deque *clients_deque;

void my_sleep()
{
    for (int i = 0; i < 0xffffffff * 10; ++i);
}

int main()
{
    init_oc();
    printf("PID of the Central Scheduler : %d\n", getpid());
    fflush(stdout);

    while(1)
    {
        my_sleep();
        schedule();
    }

    end_oc();
    return 0;
}
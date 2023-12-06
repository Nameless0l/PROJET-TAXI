#include "../include/oc.h"
#include "../include/list.h"
#include "../include/defines.h"

#include <stdio.h>
#include <unistd.h>

List *bikes_list;
List *clients_list;

void *ui_shm;
HeadGData *corresponding_gDatas;

int main(int argc, char **argv)
{
    //if(argc < 2) return EXIT_FAILURE;

    pid_t ui_pid;// = atoi(argv[1]);
    
    corresponding_gDatas = create_gData_head();

    create_ui_memory();
    init_oc();
    
    printf("Central Scheduler's PID : %d\n\n", getpid());
    fflush(stdout);

    while(1)
    {
        my_sleep();
        schedule(ui_pid);
    }

    end_oc(ui_pid);

    return 0;
}
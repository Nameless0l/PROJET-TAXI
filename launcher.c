#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{

    pid_t oc_pid = fork();
    if (oc_pid == -1)
    {
        fprintf(stderr, "Error, cannot start OC process\n");
        return -1;
    }

    if (oc_pid == 0)
    {
        // child
        char* args[] = {"./OC/bin/oc.out", NULL};
        execvp("./OC/bin/oc.out", args);
    }
    else 
    {
        // parent
        char str_oc_pid[255] = "";
        sprintf(str_oc_pid, "%d", oc_pid);
        char* args[] = {"./RPG/bin/rpg.out", str_oc_pid, NULL};
        execvp("./RPG/bin/rpg.out", args);
    }

    return 0;
}

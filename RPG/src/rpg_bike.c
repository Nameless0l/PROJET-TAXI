#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define FORK_ERROR -1
#define MAX_TIME 5

int main(int argc, char *argv[])
{
    while (1)
    {
        sleep(rand() % MAX_TIME + 1);

        pid_t pid = fork();
        if (pid == FORK_ERROR)
            printf("ERROR");

        if (pid == 0)
        {
            execv("../../moto/bin/bike.out", argv + 1);
            printf("New Bike Created %d \n", getpid());
        }
    }
    return 0;
}

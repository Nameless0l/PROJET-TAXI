#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAX_SLEEP_TIME 2
#define CLIENT_GENERATION_FREQ 2

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int balance = 0;

    while (1)
    {
        pid_t pid = fork();
        if (pid == -1)
            fprintf(stderr, "Error, cannot start neither bike or client process\n");

        if (pid == 0)
        {
            if (balance % 2)
            {
                char* args[] = {"../../client/bin/client.out", argv[1], NULL};
                execvp("../../client/bin/client.out", args);
            }
            else
            {
                char* args[] = {"../../moto/bin/bike.out", argv[1], NULL};
                execvp("../../moto/bin/bike.out", args);
            }
        }

        balance++;
        sleep(1);
    }

    return 0;
}

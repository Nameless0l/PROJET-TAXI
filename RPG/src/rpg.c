#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAX_SLEEP_TIME 5

int main(int argc, char *argv[])
{
    while (1)
    {
        pid_t pid = fork();
        if (pid == -1)
            fprintf(stderr, "Error, cannot start neither bike or client process\n");

        if (pid == 0)
        {
            srand(time(NULL));
            if ((rand()%10) % 2 == 0)
            {
                char* args[] = {"../../moto/bin/bike.out", argv[1], NULL};
                execvp("../../moto/bin/bike.out", args);
            }
            else
            {
                char* args[] = {"../../client/bin/client.out", argv[1], NULL};
                execvp("../../client/bin/client.out", args);
            }
        }

        sleep(rand() % MAX_SLEEP_TIME + 1);
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child %d ", getpid());
    }
    else
    {
        printf("Parent PID is wait for child PId %d\n", getpid());
        kill(pid, SIGTERM);
        printf("Parent is wait for 120s");

        sleep(120);
    }
    return 0;
}
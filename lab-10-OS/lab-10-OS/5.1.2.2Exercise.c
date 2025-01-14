
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
        printf("Child is wait for the parent %d \n", getpid());
        kill(getppid(), SIGTERM);
        printf("child is wait for 120s\n");
        sleep(120);
    }
    else
    {
        printf("Parent PID is wait for creating throught child PId %d\n", getpid());
    }
    return 0;
}
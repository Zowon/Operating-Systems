#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, pid;
    pid = fork();
    if (pid > 0)
    {
        sleep(120);
    }
    else if (pid == 0)
    {
        exit(0);
    }
}

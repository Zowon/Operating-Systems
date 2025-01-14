#include <unistd.h>
#include <stdio.h>

int main()
{
    int p;
    printf("P1: Main Assembly started, pid = %d\n", getpid());

    p = fork();

    if (p == 0)
    {
        fork();
        printf("sub-assembly = %d, PPID = %d\n", getpid(), getppid());

        if (p == 0)
        {
            fork();
            printf("Part A1 = %d,  \n", getpid(), getppid());
            printf("Part A1 = %d,  Part A2= %d\n", getpid(), getppid());
        }
        else
        {
            printf("part B1 PID = %d, part B2  = %d\n", getpid(), p);
            fork();
        }
    }
    else
    {
        fork();
        printf("Parent PID = %d, Child ID = %d\n", getpid(), p);
    }

    return 0;
}
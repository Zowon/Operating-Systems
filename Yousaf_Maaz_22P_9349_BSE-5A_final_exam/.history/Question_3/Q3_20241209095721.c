#include <unistd.h>
#include <stdio.h> 

int main()
{
    int p;
    printf("Original Process, pid = %d\n", getpid());
    
    p = fork();
    
    if (p == 0)
    {
        printf("Child PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(120);
    }
    else
    {
        printf("Parent PID = %d, Child ID = %d\n", getpid(), p);
        sleep(120);
    }
    
    return 0;
}
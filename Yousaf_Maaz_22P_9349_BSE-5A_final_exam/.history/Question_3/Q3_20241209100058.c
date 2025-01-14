#include <unistd.h>
#include <stdio.h> 

int main()
{
    int p;
    printf("P1: Main , pid = %d\n", getpid());
    
    p = fork();
    
    if (p == 0)
    {
        fork();
        printf("Child PID = %d, PPID = %d\n", getpid(), getppid());
        
    }
    else
    {
        fork();
        printf("Parent PID = %d, Child ID = %d\n", getpid(), p);
       
    }
    
    return 0;
}
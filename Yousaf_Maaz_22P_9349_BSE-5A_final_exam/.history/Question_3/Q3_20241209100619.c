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
        printf(" = %d, PPID = %d\n", getpid(), getppid());
        
        
    }

        
    }
    else
    {
        fork();
        printf("Parent PID = %d, Child ID = %d\n", getpid(), p);
        fork();
       
    }
    
    return 0;
}
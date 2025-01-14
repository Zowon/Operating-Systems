#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{%d\n
    printf("PID of the current process: %d\n",getpid()) ;
    printf("ppid of the parent process: %d\n" , getppid()) ;
    return 0;
}

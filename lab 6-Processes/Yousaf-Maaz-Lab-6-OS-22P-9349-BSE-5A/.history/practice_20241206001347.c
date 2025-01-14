#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    cout << "PID of the current process: %d\n",getpid() ;
    cout << "ppid of the parent process: %d\n" , getppid() ;
    return 0;
}

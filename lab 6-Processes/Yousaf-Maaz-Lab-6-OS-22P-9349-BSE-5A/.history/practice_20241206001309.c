#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    cout << "PID of the current process: %d/" << getpid() ;
    cout << "ppid of the parent process:" << getppid() ;
    return 0;
}

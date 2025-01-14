#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>


int main()
{
    cout << "PID of the current process: " << getpid() << endl;
    cout << "ppid of the parent process:" << getppid() << endl;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    // printf("Hello from OS lab\n");
    // printf("Running the linux command\n");
    // system("ls");
    
    printf("PID of the child process : %d\n", getpid());
    printf("PPID of the parent process : %d\n", getppid());
    
    return 0;
}

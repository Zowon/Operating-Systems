#include <unistd.h>
int main()
{
    int pid;          // for storing fork() return
    int pfd[2];       // for pipe file descriptors
    char aString[20]; // Temporary storage
    pipe(pfd);        // create our pipe
    pid = fork();     // create child proce
    if (pid == 0)     // For child
    {
        write(pfd[1], "Hello", 5); // Write onto pipe
    }
    else // For parent
    {
        read(pfd[0], aString, 5); // Read from pipe
    }
}
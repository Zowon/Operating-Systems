#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 25

int main()
{
    char read_msg[BUFFER_SIZE];
    char write_msg[] = "Hello";
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        printf("reation failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {

        printf("Fork failed\n");
        return 1;
    }

    if (pid > 0)
    {

        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
    }
    else
    {

        close(fd[1]);
        read(fd[0], read_msg, BUFFER_SIZE);
        printf("Received message: %s\n", read_msg);
        close(fd[0]);
    }

    return 0;
}
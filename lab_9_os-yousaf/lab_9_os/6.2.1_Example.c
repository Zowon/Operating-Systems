#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main()
{
    int pfd[2];
    pipe(pfd);
    if (fork() == 0)
    {
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        execlp("wc", "wc", (char *)0);
    }
    else
    {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);
        execlp("ls", "ls", (char *)0);
    }
}
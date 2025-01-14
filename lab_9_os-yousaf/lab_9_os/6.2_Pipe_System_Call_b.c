#include <unistd.h>
#include <stdio.h>
int main()
{
    int pfd[2];
    pipe(pfd);
    printf("write the  pipe: %d\n",pfd[1]);
    printf("Read the pipe: %d\n",pfd[0]);
}
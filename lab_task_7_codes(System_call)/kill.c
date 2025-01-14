#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    printf("Hello");
    kill(getpid(), 9);
    printf("Goodbye");
}


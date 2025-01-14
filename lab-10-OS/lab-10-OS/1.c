#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

int main()
{
    int a = 20, b = 30;

    printf("Yousaf Maaz \n ");
    printf("22P-9349 \n ");
    printf("BSE-5A \n ");

    int c = a + b;
    printf("Sum of the two integer is %d\n", c);

    printf("This is program is to be terminated \n ");

    kill(getpid(), SIGTERM);
}
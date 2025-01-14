#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
    fork();
    printf("He\n");
    fork();
    printf("Ha\n");
    fork();
    printf("Ho\n");
}
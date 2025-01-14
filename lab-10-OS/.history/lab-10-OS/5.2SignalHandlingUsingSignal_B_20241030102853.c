#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int sigCounter = 0;
void sigHandler(int sigNum)
{
    printf("Signal received is %d\n", sigNum);
    ++sigCounter;
    printf("Signals received %d\n", sigCounter);
}
int main()
{
    //signal(SIGINT, sigHandler);
    while (1)
    {
        printf("Hello Dears\n");
        sleep(1);
    }
    return 0;
}
#include <unistd.h>
int main()
{
    int pfd[2];
    pipe(pfd);
}
#include <unistd.h>
#include <stdio.h>
int main()
{
int p;
char *arg[] = {"/usr/bin/ls", 0};
p = fork();
if (p == 0)
{
printf("Child Process\n");
execv(arg[0], arg);
printf("Child Process\n");
}
else
{
printf("Parent Process\n");
}
}

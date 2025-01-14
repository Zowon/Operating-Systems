// Fork code 2
#include <unistd.h>
#include <stdio.h> // For printf()
int main()
{
int p;
printf("Original Process,pid = %d\n", getpid() );
p = fork();

if (p == 0)
{
printf("Child PID = %d, PPID = %d\n",getpid(), getppid() );
}
else
{
printf("Parent PID = %d, Child ID = %d\n",
getpid(), p);
}
}
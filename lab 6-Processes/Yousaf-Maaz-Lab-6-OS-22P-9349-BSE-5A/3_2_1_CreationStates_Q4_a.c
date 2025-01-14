#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
int count=0;
int i;
printf("Process PID %6d \t PPID %6d \n",
getpid(), getppid());
for (i = 0; i<100; ++i)
{
if (fork()==0)
printf("Process PID %6d \t PPID %6d \n",
getpid(), getppid());
count++;
printf(" count of the fork is:%d", count);
}

return 0;
}
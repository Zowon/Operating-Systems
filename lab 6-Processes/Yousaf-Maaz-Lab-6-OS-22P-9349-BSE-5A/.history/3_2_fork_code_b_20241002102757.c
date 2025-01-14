// Fork code 1
#include <unistd.h>
#include <stdio.h> // See Question 2
int main()
{
int p;
p = fork();
printf("Job Done\n");
printf("Value of P is %d\n", p);
}
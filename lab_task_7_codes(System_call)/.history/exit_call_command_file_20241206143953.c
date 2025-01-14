#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    void anotherExit(); // Function Prototype
    printf("Enter a Number: ");
    scanf("%i", &num);
    if (num > 25)
    {
        printf("exit 1\n");
        exit(1);
    }
    else
        anotherExit();
}
void anotherExit()
{
    printf("Exit 2\n");
    exit(1);
}

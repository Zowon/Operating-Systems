#include <stdio.h>

int main()
{
    int num=5, i;
    // printf("Enter a number to Display table: ");
    // scanf("%d", &num);

    printf("Table of %d:\n", num);
    for (i = 1; i <= 10; i++)
    {
        printf("%d x %d = %d\n", num, i, num * i);
    }
    return 0;
}

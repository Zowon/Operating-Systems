#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void p1(int pipe1[])
{
    close(pipe1[0]); 
    const char *filenames[] = {"sending image1.jpg", NULL};
    for (int i = 0; filenames[i] != NULL; i++)
    {
        write(pipe1[1], filenames[i], strlen(filenames[i]) + 1);
    }
    close(pipe1[1]); 
}

void p2(int pipe1[], int pipe2[])
{
    close(pipe1[1]); 
    close(pipe2[0]); 
    char filename[100];
    while (read(pipe1[0], filename, sizeof(filename)))
    {
        printf("Recevied images1.jpg and resizing it to \n");
        strcat(filename, "_resized");
        write(pipe2[1], filename, strlen(filename) + 1);
    }
    close(pipe1[0]);
    close(pipe2[1]);
}

void p3(int pipe2[], int pipe3[])
{
    close(pipe2[1]); 
    close(pipe3[0]); 
    char filename[100];
    while (read(pipe2[0], filename, sizeof(filename)))
    {
        printf("Analyzing images1.jpg and resizing it to \n");
        strcat(filename, "_analyzed");
        write(pipe3[1], filename, strlen(filename) + 1);
    }
    close(pipe2[0]);
    close(pipe3[1]);
}

void p4(int pipe3[])
{
    close(pipe3[1]); // Close write end
    char filename[100];
    while (read(pipe3[0], filename, sizeof(filename)))
    {
        printf("Distributing: %s\n", filename);
    }
    close(pipe3[0]);
}

int main()
{
    int pipe1[2], pipe2[2], pipe3[2];
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

    if (fork() == 0)
        p1(pipe1);
    if (fork() == 0)
        p2(pipe1, pipe2);
    if (fork() == 0)
        p3(pipe2, pipe3);
    if (fork() == 0)
        p4(pipe3);

    return 0;
}
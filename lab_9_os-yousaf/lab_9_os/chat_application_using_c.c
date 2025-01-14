

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main() {
    int pfd1[2], pfd2[2]; 
    pid_t pid;
    char message[BUFFER_SIZE];

    if (pipe(pfd1) == -1 || pipe(pfd2) == -1) 
    {
        printf("Pipe creation failed!\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) 
    {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid == 0) 
    {  
        while (1) 
	{
            close(pfd1[1]);  
            read(pfd1[0], message, BUFFER_SIZE);
            printf("Chat1  1 says: %s\n", message);

            
            printf("chat2: ");
            fgets(message, BUFFER_SIZE, stdin);
            message[strcspn(message, "\n")] = 0; 
            close(pfd2[0]);  
            write(pfd2[1], message, strlen(message) + 1);
        }
    } 
    else 
    { 
        while (1) 
	{
            printf("Chat1: ");
            fgets(message, BUFFER_SIZE, stdin);
            message[strcspn(message, "\n")] = 0;  
            close(pfd1[0]);  
            write(pfd1[1], message, strlen(message) + 1);

            close(pfd2[1]);  
            read(pfd2[0], message, BUFFER_SIZE);
            printf("chat2 says: %s\n", message);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080

void *receive_messages(void *arg) {
    int socket_fd = *(int *)arg;
    char buffer[1024];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(socket_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("Disconnected from server.\n");
            pthread_exit(NULL);
        }
        printf("Server: %s\n", buffer);
    }
}

int main() {
    int socket_fd;
    struct sockaddr_in server_address;
    char message[1024];

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server. Type 'exit' to disconnect.\n");

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, receive_messages, (void *)&socket_fd) != 0) {
        perror("Thread creation failed");
        return -1;
    }

    while (1) {
        memset(message, 0, sizeof(message));
        printf("You: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;

        if (strcmp(message, "exit") == 0) {
            printf("Disconnecting...\n");
            break;
        }

        send(socket_fd, message, strlen(message), 0);
    }

    close(socket_fd);
    return 0;
}

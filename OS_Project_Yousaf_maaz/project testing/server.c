#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10

int client_sockets[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t lock;

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[1024];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("Client disconnected.\n");
            close(client_socket);

            pthread_mutex_lock(&lock);
            for (int i = 0; i < client_count; i++) {
                if (client_sockets[i] == client_socket) {
                    client_sockets[i] = client_sockets[client_count - 1];
                    client_count--;
                    break;
                }
            }
            pthread_mutex_unlock(&lock);

            pthread_exit(NULL);
        }

        printf("Received from client: %s\n", buffer);

        // Ask the server user whether to broadcast a custom message
        printf("Do you want to send a message to all clients? (yes/no): ");
        char choice[10];
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0; // Remove trailing newline

        if (strcmp(choice, "yes") == 0) {
            printf("Enter message to broadcast: ");
            char broadcast_msg[1024];
            fgets(broadcast_msg, sizeof(broadcast_msg), stdin);
            broadcast_msg[strcspn(broadcast_msg, "\n")] = 0;

            pthread_mutex_lock(&lock);
            for (int i = 0; i < client_count; i++) {
                send(client_sockets[i], broadcast_msg, strlen(broadcast_msg), 0);
            }
            pthread_mutex_unlock(&lock);
        } else {
            printf("Acknowledged: %s\n", buffer);
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    pthread_mutex_init(&lock, NULL);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New client connected.\n");

        pthread_mutex_lock(&lock);
        client_sockets[client_count++] = new_socket;
        pthread_mutex_unlock(&lock);

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&new_socket) != 0) {
            perror("Thread creation failed");
        }
    }

    pthread_mutex_destroy(&lock);
    close(server_fd);

    return 0;
}

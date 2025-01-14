#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX_CONNECTIONS 5

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_address, client_address;
    int addr_len = sizeof(client_address);
    char buffer[1024] = {0};
    char *welcome_message = "Server: Connection established.\n";

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP
    server_address.sin_port = htons(PORT);

    // Bind the socket to the specified port and IP
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept client connection
    if ((client_socket = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&addr_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected from IP: %s, Port: %d\n",
           inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // Send welcome message to the client
    send(client_socket, welcome_message, strlen(welcome_message), 0);

    // Communicate with the client
    while (1) {
        int valread = read(client_socket, buffer, sizeof(buffer));
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Client: %s", buffer);  // Display the client's message
        } else {
            printf("Client disconnected.\n");
            break;
        }

        // Respond to the client
        printf("Enter message for client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    // Close the connection
    close(client_socket);
    close(server_fd);

    return 0;
}

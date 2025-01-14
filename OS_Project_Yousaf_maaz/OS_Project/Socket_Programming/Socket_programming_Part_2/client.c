#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert server IP to binary form
    if (inet_pton(AF_INET, "192.168.1.55", &server_address.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");

    // Receive the welcome message
    int valread = read(client_socket, buffer, sizeof(buffer));
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("%s", buffer);
    }

    // Communicate with the server
    while (1) {
        // Send message to the server
        printf("Enter message for server: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);

        // Receive server response
        valread = read(client_socket, buffer, sizeof(buffer));
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Server: %s", buffer);
        } else {
            printf("Server disconnected.\n");
            break;
        }
    }

    // Close the connection
    close(client_socket);

    return 0;
}

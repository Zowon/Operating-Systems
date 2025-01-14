#include <stdio.h>      // Standard input/output functions
#include <stdlib.h>     // Standard library functions
#include <string.h>     // String manipulation functions
#include <sys/socket.h> // Socket programming functions
#include <arpa/inet.h>  // Internet address manipulation functions
#include <unistd.h>     // POSIX API (e.g., close)

#define PORT 8080         // Port number for the server
#define MAX_CONNECTIONS 5 // Maximum number of pending connections

int main()
{
    int server_fd, client_socket;                                // Server and client socket file descriptors
    struct sockaddr_in server_address, client_address;           // Server and client address structures
    int addr_len = sizeof(client_address);                       // Length of the client address structure
    char buffer[1024] = {0};                                     // Buffer to store messages
    char *welcome_message = "Server: Connection established.\n"; // Welcome message for the client

    // Step 1: Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed"); // Print error if socket creation fails
        exit(EXIT_FAILURE);      // Exit with failure
    }

    // Step 2: Configure server address structure
    server_address.sin_family = AF_INET;         // Use IPv4
    server_address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    server_address.sin_port = htons(PORT);       // Convert port number to network byte order

    // Step 3: Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Bind failed"); // Print error if binding fails
        exit(EXIT_FAILURE);    // Exit with failure
    }

    // Step 4: Listen for incoming connections
    if (listen(server_fd, MAX_CONNECTIONS) < 0)
    {
        perror("Listen failed"); // Print error if listening fails
        exit(EXIT_FAILURE);      // Exit with failure
    }

    printf("Server is listening on port %d...\n", PORT);

    // Step 5: Accept a client connection
    if ((client_socket = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&addr_len)) < 0)
    {
        perror("Accept failed"); // Print error if accepting a connection fails
        exit(EXIT_FAILURE);      // Exit with failure
    }

    // Print details of the connected client
    printf("Client connected from IP: %s, Port: %d\n",
           inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // Step 6: Send a welcome message to the client
    send(client_socket, welcome_message, strlen(welcome_message), 0);

    // Step 7: Communicate with the client
    while (1)
    {
        // Receive a message from the client
        int valread = read(client_socket, buffer, sizeof(buffer));
        if (valread > 0)
        {
            buffer[valread] = '\0';       // Null-terminate the received message
            printf("Client: %s", buffer); // Display the client's message
        }
        else
        {
            // If no bytes are read, the client has disconnected
            printf("Client disconnected.\n");
            break;
        }

        // Prompt the server to enter a response
        printf("Enter message for client: ");
        fgets(buffer, sizeof(buffer), stdin);           // Read input from the server user
        send(client_socket, buffer, strlen(buffer), 0); // Send the message to the client
    }

    // Step 8: Close the connections
    close(client_socket); // Close the client socket
    close(server_fd);     // Close the server socket

    return 0; // Exit successfully
}

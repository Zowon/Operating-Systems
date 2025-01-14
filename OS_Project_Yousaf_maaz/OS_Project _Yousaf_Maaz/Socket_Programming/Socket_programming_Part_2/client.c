#include <stdio.h>      // Standard input/output functions
#include <stdlib.h>     // Standard library functions
#include <string.h>     // String manipulation functions
#include <sys/socket.h> // Socket programming functions
#include <arpa/inet.h>  // Internet address manipulation functions
#include <unistd.h>     // POSIX API (e.g., close)

#define PORT 8080 // The port number to connect to the server

int main()
{
    int client_socket;                 // File descriptor for the client socket
    struct sockaddr_in server_address; // Structure to store the server's address
    char buffer[1024] = {0};           // Buffer to store messages

    // Step 1: Create a socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed"); // Print error if socket creation fails
        exit(EXIT_FAILURE);               // Exit with failure
    }

    // Step 2: Configure server address structure
    server_address.sin_family = AF_INET;   // Use IPv4
    server_address.sin_port = htons(PORT); // Convert port number to network byte order

    // Step 3: Convert server IP address to binary form
    if (inet_pton(AF_INET, "192.168.161.27", &server_address.sin_addr) <= 0)
    {
        perror("Invalid address or address not supported"); // Error if the IP is invalid
        exit(EXIT_FAILURE);                                 // Exit with failure
    }

    // Step 4: Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection failed"); // Print error if connection fails
        exit(EXIT_FAILURE);          // Exit with failure
    }

    printf("Connected to the server.\n");

    // Step 5: Receive the welcome message from the server
    int valread = read(client_socket, buffer, sizeof(buffer)); // Read the welcome message
    if (valread > 0)
    {
        buffer[valread] = '\0'; // Null-terminate the received message
        printf("%s", buffer);   // Print the welcome message
    }

    // Step 6: Communicate with the server
    while (1)
    {
        // Send a message to the server
        printf("Enter message for server: ");
        fgets(buffer, sizeof(buffer), stdin);           // Read input from the user
        send(client_socket, buffer, strlen(buffer), 0); // Send the message to the server

        // Receive a response from the server
        valread = read(client_socket, buffer, sizeof(buffer)); // Read the server's response
        if (valread > 0)
        {
            buffer[valread] = '\0';       // Null-terminate the received message
            printf("Server: %s", buffer); // Print the server's response
        }
        else
        {
            // If no bytes are read, the server has disconnected
            printf("Server disconnected.\n");
            break;
        }
    }

    // Step 7: Close the connection
    close(client_socket); // Close the client socket

    return 0; // Exit successfully
}

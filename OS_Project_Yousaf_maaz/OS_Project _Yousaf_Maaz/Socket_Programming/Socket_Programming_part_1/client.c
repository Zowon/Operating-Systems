// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <pthread.h>

// #define PORT 8080

// void *receive_messages(void *arg) {
//     int socket_fd = *(int *)arg;
//     char buffer[1024];

//     while (1) {
//         memset(buffer, 0, sizeof(buffer));
//         int bytes_received = recv(socket_fd, buffer, sizeof(buffer), 0);
//         if (bytes_received <= 0) {
//             printf("Disconnected from server.\n");
//             pthread_exit(NULL);
//         }
//         printf("Server: %s\n", buffer);
//     }
// }

// int main() {
//     int socket_fd;
//     struct sockaddr_in server_address;
//     char message[1024];

//     if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         perror("Socket failed");
//         exit(EXIT_FAILURE);
//     }

//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(PORT);

//     if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
//         perror("Invalid address");
//         exit(EXIT_FAILURE);
//     }

//     if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
//         perror("Connection failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Connected to the server. Type 'exit' to disconnect.\n");

//     pthread_t thread_id;
//     if (pthread_create(&thread_id, NULL, receive_messages, (void *)&socket_fd) != 0) {
//         perror("Thread creation failed");
//         return -1;
//     }

//     while (1) {
//         memset(message, 0, sizeof(message));
//         printf("You: ");
//         fgets(message, sizeof(message), stdin);
//         message[strcspn(message, "\n")] = 0;

//         if (strcmp(message, "exit") == 0) {
//             printf("Disconnecting...\n");
//             break;
//         }

//         send(socket_fd, message, strlen(message), 0);
//     }

//     close(socket_fd);
//     return 0;
// }

#include <stdio.h>      // For standard input/output functions
#include <stdlib.h>     // For memory management and program control functions
#include <string.h>     // For string manipulation functions
#include <sys/socket.h> // For socket-related functions
#include <arpa/inet.h>  // For handling Internet addresses
#include <unistd.h>     // For POSIX API functions like close()
#include <pthread.h>    // For multithreading

#define PORT 8080 // Port number the client will connect to

// Function to handle receiving messages from the server
void *receive_messages(void *arg)
{
    int socket_fd = *(int *)arg; // Extract the socket file descriptor
    char buffer[1024];           // Buffer to store incoming messages

    while (1)
    {
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer before receiving data
        int bytes_received = recv(socket_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        { // If no message received or server disconnects
            printf("Disconnected from server.\n");
            pthread_exit(NULL); // Exit the thread if server disconnects
        }
        printf("Server: %s\n", buffer); // Display the server's message
    }
}

int main()
{
    int socket_fd;                     // Socket file descriptor for client
    struct sockaddr_in server_address; // Struct to hold server address information
    char message[1024];                // Buffer to store messages to be sent

    // Create a socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed"); // Print error message if socket creation fails
        exit(EXIT_FAILURE);
    }

    // Define server address properties
    server_address.sin_family = AF_INET;   // Set to IPv4
    server_address.sin_port = htons(PORT); // Convert port number to network byte order

    // Convert IP address to binary form and set it
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        perror("Invalid address"); // Print error message if address conversion fails
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection failed"); // Print error message if connection fails
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server. Type 'exit' to disconnect.\n");

    // Create a thread to handle receiving messages from the server
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, receive_messages, (void *)&socket_fd) != 0)
    {
        perror("Thread creation failed"); // Print error message if thread creation fails
        return -1;
    }

    // Loop to send messages to the server
    while (1)
    {
        memset(message, 0, sizeof(message));    // Clear the message buffer
        printf("You: ");                        // Prompt user to enter a message
        fgets(message, sizeof(message), stdin); // Read user input
        message[strcspn(message, "\n")] = 0;    // Remove trailing newline character

        // If the user types 'exit', disconnect from the server
        if (strcmp(message, "exit") == 0)
        {
            printf("Disconnecting...\n");
            break;
        }

        // Send the user's message to the server
        send(socket_fd, message, strlen(message), 0);
    }

    close(socket_fd); // Close the socket when done
    return 0;
}

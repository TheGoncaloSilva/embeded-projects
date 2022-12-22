#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SUCCESS 1 << 0
#define FAILURE 1 << 1

int main(int argc, char const *argv[])
{
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Set the address and port to bind the socket to
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = 0x4c01a8c0;

    // Bind the socket to the address and port
    bind(sock, (struct sockaddr*) &addr, sizeof(addr));

    // Listen for incoming connections
    listen(sock, 2);

    // Accept an incoming connection
    int client_sock = accept(sock, NULL, NULL);


    while (1){

        // Send a response to the client
        char* response = "HELLO, client!";
        send(client_sock, response, strlen(response), 0);

        // Receive a message from the client
        char message[1024];
        recv(client_sock, message, sizeof(message), 0);
    }
    
    // Receive a message from the client
    //char message[1024];
    //recv(client_sock, message, sizeof(message), 0);

    // Print the received message
    //printf("Received from the client: %s\n", message);

    // Send a response to the client
    char* response = "HELLO, client!";
    send(client_sock, response, strlen(response), 0);

    // Close the client socket
    close(client_sock);

    // Close the server socket
    close(sock);

    return SUCCESS;
}


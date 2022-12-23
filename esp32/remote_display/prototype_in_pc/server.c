#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SUCCESS 1 << 0
#define FAILURE 1 << 1
#define MAX_INPUT 15

int main(int argc, char const *argv[])
{
    /* Instanciate objects */
    int server_socket, client_socket, c;
    struct sockaddr_in server, client;
    char input[MAX_INPUT], recv_msg[MAX_INPUT];

    // Create the socket
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "Socket couldn't be created\n");
        return FAILURE;
    }

    // Set the address and port to bind the socket to
    
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;//0x4c01a8c0;

    // Bind the socket to the address and port
    if( bind(server_socket, (struct sockaddr*)&server, sizeof(server)) < 0){
        fprintf(stderr, "Failure to create server\n");
        return FAILURE;
    }
    
    // Listen for incoming connections
    listen(server_socket, 5);

    fprintf(stdout, "Listenning on localhost:8080\n");

    // Accept an incoming connection
    if( client_socket = accept(server_socket,(struct sockaddr*)&client, (socklen_t*)&c) < 0 ){
        fprintf(stderr, "Failed client connection\n");
        return FAILURE;
    }
    fprintf(stdout, "Client accepted\n");

    while (1){
        
        fprintf(stdout, "Message to send: ");
        scanf("%s", input);
        // Send a response to the client
        if(send(client_socket, input, strlen(input), 0) < 0)
            break;

        // Receive a message from the client
        if(recv(client_socket, recv_msg, sizeof(recv_msg), 0) < 0)
            break;

        puts("Received message: ");
        puts(recv_msg);
    }

    fprintf(stdout, "Client disconnected\n");

    // Close the client socket
    close(client_socket);

    // Close the server socket
    close(server_socket);

    return SUCCESS;
}


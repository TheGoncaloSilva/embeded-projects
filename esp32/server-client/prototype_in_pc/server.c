#include <stdio.h>          // fprintf(), puts(), pclose()
#include <unistd.h>         // close()
#include <string.h>         // strlen()
#include <stdlib.h>         // atoi()
#include <sys/socket.h>     // socket(), connect()
#include <netinet/in.h>     // struct sockaddr_in
#include <sys/types.h>      // AF_INET, SOCK_STREAM
#include <arpa/inet.h>      // htons(), inet_addr()

#define SUCCESS 1 << 0
#define FAILURE 1 << 1
#define MAX_MSG_LEN 256
#define PORT 8080
#define ADDRESS "192.168.1.76"//"127.0.0.1"

int main(int argc, char const *argv[])
{

    /* Instanciate objects */
    int server_socket, client_socket, c, status, port;
    struct sockaddr_in server, client; /* This struct is created in the stack, so it needs to be initialized befor use */
    char input[MAX_MSG_LEN], recv_msg[MAX_MSG_LEN];

    // Check if an argument was provided
    if (argc < 2)
        port = PORT;
    else
        port = atoi(argv[1]); // Convert the argument to an integer

    // Create the socket
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "Socket couldn't be created\n");
        return FAILURE;
    }

    // Set the address and port to bind the socket to
    memset(&client, 0, sizeof(client));
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ADDRESS); // INADDR_ANY;

    // Bind the socket to the address and port
    if( bind(server_socket, (struct sockaddr*)&server, sizeof(server)) < 0){
        fprintf(stderr, "Failure to create server\n");
        return FAILURE;
    }
    
    // Listen for incoming connections
    if(listen(server_socket, 3) < 0){
        fprintf(stderr, "Listen failed");
        return FAILURE;
    }

    fprintf(stdout, "Listenning on %s:%d\n", ADDRESS, port);

    // Accept an incoming connection
    if( (client_socket = accept(server_socket,(struct sockaddr*)&client, (socklen_t*)&c)) < 0 ){
        fprintf(stderr, "Failed client connection\n");
        return FAILURE;
    }
    fprintf(stdout, "Client accepted\n");

    while (1){
        
        /* Reset messages */
        memset(&input, 0, sizeof(input));
        memset(&recv_msg, 0, sizeof(recv_msg));

        fprintf(stdout, "Request to send: ");
        scanf("%s", input);

        // Send a request to the client
        if( (status = send(client_socket, input, strlen(input), 0)) <= 0)
            break;

        // Receive a response from the client
        if( (status = recv(client_socket, recv_msg, MAX_MSG_LEN, 0)) < 0)
            break;

        fprintf(stdout, "Received from client: %s \n", recv_msg);
    }

    if(status == 0){
        fprintf(stdout, "Client disconnected\n");
    }

    if(status == 1){
        fprintf(stdout, "Receive/Send error\n");
        return FAILURE;
    }

    // Close the client socket
    close(client_socket);

    // Close the server socket
    close(server_socket);

    return SUCCESS;
}


#include <stdio.h>          // fprintf(), puts(), pclose()
#include <unistd.h>         // close(), read(), write()
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
#define ADDRESS "127.0.0.1"
#define FALSE 0
#define TRUE 1


int check_request(char *request){
    if(strlen(request) > 6)
        return FALSE;

    const char* approved = "123456789:";

    for(int i = 0; i < strlen(request); i++){
        int counter = 0;
        for(int j = 0; j < strlen(approved); j++){
            if(request[i] == approved[j])
                counter++; 
        }
        if(!counter)
            return FALSE; // Character not approved
    }
    return TRUE;
}


int handle_request(char *request){
    if(!check_request(request))
        return FALSE;

    return TRUE;
}

int main(int argc, char const *argv[])
{
    /* Instanciate objects */
    int client_socket, status, port;
    struct sockaddr_in server; /* This struct is created in the stack, so it needs to be initialized befor use */
    char request[MAX_MSG_LEN];
    char* successResponse = "Success";
    char* failureResponse = "Failure";
    char* response = NULL;

    // Check if an argument was provided
    if (argc < 2)
        port = PORT;
    else
        port = atoi(argv[1]); // Convert the argument to an integer

    // Create a socket
    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "Error creating socket\n");
        return FAILURE;
    }

    // Set the address and port of the server to connect to
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ADDRESS); // INADDR_ANY;

    // Connect to the server
    if(connect(client_socket, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "Failed to connect to server\n");
        return FAILURE;
    } 

    puts("Successfully connected to server\n");

    while(1){
        // Receive a message from the server
        memset(&request, 0, sizeof(request)); // Reset buffer
        if( (status = recv(client_socket, request, MAX_MSG_LEN, 0)) <= 0)
            break;
        
        fprintf(stdout, "Received from server: %s\n", request);

        // Send a message to the server
        if(handle_request(request))
            response = successResponse; // Response points to success
        else
            response = failureResponse; // Response points to failure

        if((status = send(client_socket, response, strlen(response), 0)) < 0)
            break;
    }

    if(status == 0){
        fprintf(stdout, "Server disconnected\n");
    }

    if(status == 1){
        fprintf(stdout, "Receive/Send error\n");
        return FAILURE;
    }

    // Close the socket
    close(client_socket);

    return SUCCESS;
}


#include <stdio.h>

// Included for handling socket: socket, connect, bind, listen, accept, send, recv, sockaddr
#include <sys/socket.h>

// Included for handling file descriptor
#include <unistd.h>

// Convert ip address eg "127.0.0.1" to binary format usable for the socket
#include <arpa/inet.h>

// sockaddr_in, AF_INET
#include <netinet/in.h>

/**
 * 
 * socket(): Create the socket
 * bind(): associate ip address and port
 * listen(): wait for connections
 * accept(): accept a client and send socket to discuss with it
 * recv() and send(): send and receive data
 * close(): close the socket (the connection)
 * 
 */

int main(){
    // Create the socket
    int client = socket(AF_INET, SOCK_STREAM, 0); // TCP IPv4
    if(client == -1){
        perror("socket");
        return 1;
    }

    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;

    // htons is used to convert short int to be usable by the socket
    // socket -> short in htons() convert the sin_port to short int
    serv_addr.sin_port = htons(6969);

    // Convert the char * form of ip to ip usable by the socket "presentation to network" 
    // AF_INET stands for IPv4 address 
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Connect
    if (connect(client, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {    
        perror("connect");    
        close(client);    
        return 1;
    }

    send(client, "Bonjour", 7, 0);
    close(client);
}
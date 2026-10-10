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
    int sock = socket(AF_INET, SOCK_STREAM, 0); // TCP IPv4
    struct sockaddr_in server = {0};
    server.sin_family = AF_INET;

    // htons is used to convert short int to be usable by the socket
    // socket -> short in htons() convert the sin_port to short int
    server.sin_port = htons(8080);

    // Convert the char * form of ip to ip usable by the socket "presentation to network" 
    // AF_INET stands for IPv4 address 
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1) {    
        perror("connect");    
        close(sock);    
        return 1;
    }

    send(sock, "Bonjour", 7, 0);
    char buffer[256];
    ssize_t n = recv(sock, buffer, sizeof(buffer), 0);
    
    if (n > 0) {    
        printf("Reçu %zd octets\n", n);
    }
    close(sock);
}
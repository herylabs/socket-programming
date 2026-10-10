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

int main(int argc, char ** argv){
    int sock = socket(AF_INET, SOCK_STREAM, 0); // TCP IPv4
    struct sockaddr_in serveur = {0};
    serveur.sin_family = AF_INET;
    serveur.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serveur.sin_addr);

    if (connect(sock, (struct sockaddr *)&serveur, sizeof(serveur)) == -1) {    
        perror("connect");    
        close(sock);    
        return 1;
    }

    send(sock, "Bonjour", 7, 0);
    char buffer[256];ssize_t n = recv(sock, buffer, sizeof(buffer), 0);if (n > 0) {    printf("Reçu %zd octets\n", n);}
    close(sock);
}
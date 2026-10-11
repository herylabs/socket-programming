#include <stdio.h>
#include <string.h>

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
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); // TCP IPv4
    if(server_fd == -1){
        perror("socket");
        return 1;
    }

    // OPtion=1 relaunch the server after it is stopped
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Create th address where the server listen on
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;

    // htons is used to convert short int to be usable by the socket
    // socket -> short in htons() convert the sin_port to short int
    serv_addr.sin_port = htons(6969);

    // serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // this line is the same as (1)

    // Convert the char * form of ip to ip usable by the socket "presentation to network" 
    // AF_INET stands for IPv4 address 
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // (1)

    // bind the file descriptor not connect (to be able to accept connection)
    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {    
        perror("bind");    
        close(server_fd);    
        return 1;
    }

    // Listen on 127.0.0.1 
    if(listen(server_fd, 5) == -1){
        perror("bind");
        close(server_fd);
        return 1;
    }

    // Msg
    printf("Server listen on 127.0.0.1:6969\n");

    // THe code is blocked here till a client connect to the address
    int client_fd = accept(server_fd, NULL, NULL);
    if(client_fd == -1){
        perror("accept");
        close(server_fd);
        return 1;
    }

    printf("Client connected.\n");

    char buf[1024];
    ssize_t n;
    while ((n = recv(client_fd, buf, sizeof(buf), 0)) > 0)
    {
        fwrite(buf, 1, n, stdout);
        fflush(stdout);
    }
    
    if(n == -1)
        perror("recv");

    printf("client disconnected...\n");

    close(client_fd);
    close(server_fd);
    return 0;
}
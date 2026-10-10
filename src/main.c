#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char ** argv){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, &remote, sizeof(remote));

    write(sock, buffer, 1000000);
    close(sock);
    return 0;
}
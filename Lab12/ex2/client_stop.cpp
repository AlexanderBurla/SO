#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    char recvBuff[1024];

    if (argc != 2) {
        printf("Usage: %s <server IP>\n", argv[0]);
        return 1;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error: Could not create socket\n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("Error: Invalid address or address not supported\n");
        return 1;
    }

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error: Connect failed\n");
        return 1;
    }

    while (1) {
        int n = read(sockfd, recvBuff, sizeof(recvBuff) - 1);
        if (n <= 0) {
            break;
        }
        recvBuff[n] = 0;
        printf("Received: %s\n", recvBuff);

        if (strcmp(recvBuff, "STOP") == 0) {
            printf("Server requested stop. Exiting.\n");
            break;
        }
    }

    close(sockfd);

    return 0;
}


// gcc server_stop.c -o server_stop
// gcc client_stop.c -o client_stop

// ./server_stop

// ./"client_stop" 127.0.0.1


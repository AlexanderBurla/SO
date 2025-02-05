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
    char sendBuff[1024];
    FILE *fp;

    if (argc != 3) {
        printf("Usage: %s <server IP> <file path>\n", argv[0]);
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

    if ((fp = fopen(argv[2], "r")) == NULL) {
        printf("Error: Could not open file %s\n", argv[2]);
        close(sockfd);
        return 1;
    }

    while (fgets(sendBuff, sizeof(sendBuff), fp) != NULL) {
        write(sockfd, sendBuff, strlen(sendBuff));
    }

    fclose(fp);
    close(sockfd);

    return 0;
}
//gcc server.c -o server
//gcc client.c -o client

// ./server

// ./"client" 127.0.0.1 "/home/stud/Desktop/Lab/Lab12/ex1/file.txt"

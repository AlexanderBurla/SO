#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1024];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    printf("Server is running and waiting for connections...\n");

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    printf("Client connected.\n");

    while (1) {
        printf("Enter a message to send to the client: ");
        fgets(sendBuff, sizeof(sendBuff), stdin);
        sendBuff[strcspn(sendBuff, "\n")] = 0; // Remove newline character
        write(connfd, sendBuff, strlen(sendBuff));

        if (strcmp(sendBuff, "STOP") == 0) {
            printf("Stopping server.\n");
            sleep(1);
            break;
        }
    }

    close(connfd);
    close(listenfd);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_KEY 1234

typedef struct msg_buffer {
    long msg_type;
    int value;
} msg_buffer;

int main() {
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    msg_buffer message;

    while (1) {
        msgrcv(msgid, &message, sizeof(message.value), 1, 0);
        printf("Consumator: a consumat %d\n", message.value);
        sleep(1);
    }

    return 0;
}

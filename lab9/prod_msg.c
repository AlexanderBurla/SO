#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

#define MSG_KEY 1234

typedef struct msg_buffer {
    long msg_type;
    int value;
} msg_buffer;

int main() {
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    msg_buffer message;
    srand(time(NULL));

    while (1) {
        message.msg_type = 1;
        message.value = rand() % 100;  // Generează un număr aleator.
        msgsnd(msgid, &message, sizeof(message.value), 0);
        printf("Producător: a produs %d\n", message.value);
        sleep(1);
    }

    return 0;
}

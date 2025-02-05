#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define MSG_KEY 1234

// Structura mesajului
struct message {
    long msg_type;
    float value;
};

int main() {
    srand(time(NULL));

    // Accesare coadă de mesaje
    int msgid = msgget(MSG_KEY, 0666);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    struct message msg;

    while (1) {
        // Primește mesajul
        if (msgrcv(msgid, &msg, sizeof(msg.value), 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("Consumator: consumat %.2f\n", msg.value);

        // Așteaptă între 500 și 1500 ms
        int wait_time = 500 + rand() % 1001;
        usleep(wait_time * 1000);
    }

    return 0;
}

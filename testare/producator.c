#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define BUFFER_SIZE 10
#define MSG_KEY 1234

// Structura mesajului
struct message {
    long msg_type;
    float value;
};

// Funcție pentru generare număr aleator float în intervalul [0, 30.00]
float generate_random_float() {
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 30.0));
}

int main() {
    srand(time(NULL));

    // Creare/colectare coadă de mesaje
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    struct message msg;
    msg.msg_type = 1;

    while (1) {
        // Generează valoare și trimite
        msg.value = generate_random_float();
        if (msgsnd(msgid, &msg, sizeof(msg.value), 0) < 0) {
            perror("msgsnd");
            exit(1);
        }
        printf("Producător: produs %.2f\n", msg.value);
        sleep(1); // Așteaptă o secundă
    }

    return 0;
}

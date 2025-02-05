#include "coada.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

int g_nIdB0;

void creazaB0() {
    if ((g_nIdB0 = msgget(KEY, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
    }
}

int main() {
    creazaB0();
    Mesaj msg;
    for (int i = 1; i <= 1000; i++) {
        msg.nTip = 1;  // Tip generic
        sprintf(msg.achData, "%d", i);
        if (msgsnd(g_nIdB0, &msg, sizeof(Mesaj), 0) < 0) {
            perror("msgsnd");
        } else {
            printf("P0: Am trimis %s\n", msg.achData);
        }
        sleep(1);
    }
    // Trimitem "0" ca semnal de terminare
    sprintf(msg.achData, "0");
    msgsnd(g_nIdB0, &msg, sizeof(Mesaj), 0);
    return 0;
}

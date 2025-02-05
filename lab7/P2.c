#include "coada.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

int g_nIdB1;

void creazaB1() {
    if ((g_nIdB1 = msgget(KEY + 1, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
    }
}

int main() {
    creazaB1();
    Mesaj msg;
    while (1) {
        if (msgrcv(g_nIdB1, &msg, sizeof(Mesaj), 0, 0) < 0) {
            perror("msgrcv");
        } else {
            int num = atoi(msg.achData);
            if (num == 0) {
                break;  // Semnal de terminare
            }
            if (num % 3 != 0) {
                printf("P2: Afișez %d\n", num);
            } else {
                printf("P2: Ignorat %d (divizibil cu 3)\n", num);
            }
        }
        sleep(1);
    }
    return 0;
}

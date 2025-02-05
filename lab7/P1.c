#include "coada.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

int g_nIdB0, g_nIdB1;

void creazaB0B1() {
    if ((g_nIdB0 = msgget(KEY, IPC_CREAT | 0666)) < 0) {
        perror("msgget B0");
    }
    if ((g_nIdB1 = msgget(KEY + 1, IPC_CREAT | 0666)) < 0) {
        perror("msgget B1");
    }
}

int main() {
    creazaB0B1();
    Mesaj msg;
    while (1) {
        if (msgrcv(g_nIdB0, &msg, sizeof(Mesaj), 0, 0) < 0) {
            perror("msgrcv");
        } else {
            int num = atoi(msg.achData);
            if (num == 0) {
                msgsnd(g_nIdB1, &msg, sizeof(Mesaj), 0);  // Semnal de terminare
                break;
            }
            if (num % 2 != 0) {
                msgsnd(g_nIdB1, &msg, sizeof(Mesaj), 0);
                printf("P1: Am trimis %s\n", msg.achData);
            } else {
                printf("P1: Ignorat %d (divizibil cu 2)\n", num);
            }
        }
        sleep(1);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> // for sleep

#define KEY_MEM 2345
#define MEM_SIZE 1024

int main() {
    int memID;
    char *pMem;

    // Obține ID-ul memoriei partajate
    memID = shmget(KEY_MEM, MEM_SIZE, 0666);
    if (memID == -1) {
        printf("Eroare obtinere ID memorie partajata\n");
        return 1;
    }
    printf("ID-ul Memoriei partajate a fost obtinut cu succes\n");

    // Atașare memorie partajată
    pMem = (char *)shmat(memID, NULL, 0);
    if (pMem == (char *)-1) {
        printf("Eroare atasare memorie partajata\n");
        return 1;
    }
    printf("Memoria partajata a fost atasata cu succes\n");

    // Citire mesaje din memorie
    while (1) {
        printf("Mesaj citit: %s\n", pMem);
        if (strcmp(pMem, "STOP") == 0) {
            break;
        }
        sleep(1); // Pauză de 1 secundă
    }

    // Detasare memorie
    if (shmdt(pMem) == -1) {
        printf("Eroare detasare memorie partajata\n");
    }
    printf("Memoria partajata a fost detasata cu succes\n");

    return 0;
}

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

    // Creare memorie partajată
    memID = shmget(KEY_MEM, MEM_SIZE, IPC_CREAT | 0666);
    if (memID == -1) {
        printf("Eroare creare memorie partajata\n");
        return 1;
    }
    printf("Memoria partajata a fost creata cu succes\n");

    // Atașare memorie partajată
    pMem = (char *)shmat(memID, NULL, 0);
    if (pMem == (char *)-1) {
        printf("Eroare atasare memorie partajata\n");
        return 1;
    }
    printf("Memoria partajata a fost atasata cu succes\n");

    // Scriere mesaje în memorie
    char input[MEM_SIZE];
    while (1) {
        printf("Introduceti un mesaj: ");
        fgets(input, MEM_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0'; // Elimină newline-ul

        strcpy(pMem, input);

        if (strcmp(input, "STOP") == 0) {
            sleep(1);
            break;
        }
    }

    // Detasare și ștergere memorie
    if (shmdt(pMem) == -1) {
        printf("Eroare detasare memorie partajata\n");
    }
    if (shmctl(memID, IPC_RMID, NULL) == -1) {
        printf("Eroare stergere memorie partajata\n");
    }
    printf("Memoria partajata a fost stearsa cu succes\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> // for sleep

#define KEY_B0 3456
#define MEM_SIZE sizeof(int)

int main() {
    int memID;
    int *pMem;

    // Create shared memory for B0
    memID = shmget(KEY_B0, MEM_SIZE, IPC_CREAT | 0666);
    if (memID == -1) {
        printf("Eroare creare memorie partajata pentru B0\n");
        return 1;
    }
    printf("Memoria partajata B0 a fost creata cu succes\n");

    // Attach shared memory
    pMem = (int *)shmat(memID, NULL, 0);
    if (pMem == (int *)-1) {
        printf("Eroare atasare memorie partajata pentru B0\n");
        return 1;
    }
    printf("Memoria partajata B0 a fost atasata cu succes\n");

    // Generate numbers and write to B0
    for (int i = 1; i <= 1000; i++) {
        *pMem = i;
        printf("Scris in B0: %d\n", i);
        sleep(1);
    }

    // Write 0 to indicate termination
    *pMem = 0;
    printf("Scris in B0: 0\n");

    // Detach and destroy shared memory
    if (shmdt(pMem) == -1) {
        printf("Eroare detasare memorie partajata pentru B0\n");
    }
    if (shmctl(memID, IPC_RMID, NULL) == -1) {
        printf("Eroare stergere memorie partajata pentru B0\n");
    }
    printf("Memoria partajata B0 a fost stearsa cu succes\n");

    return 0;
}

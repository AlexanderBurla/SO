#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> // for sleep

#define KEY_B0 3456
#define KEY_B1 4567
#define MEM_SIZE sizeof(int)

int main() {
    int memID_B0, memID_B1;
    int *pMem_B0, *pMem_B1;

    // Access shared memory for B0
    memID_B0 = shmget(KEY_B0, MEM_SIZE, 0666);
    if (memID_B0 == -1) {
        printf("Eroare obtinere ID memorie partajata pentru B0\n");
        return 1;
    }
    printf("ID-ul Memoriei partajate B0 a fost obtinut cu succes\n");

    // Attach shared memory for B0
    pMem_B0 = (int *)shmat(memID_B0, NULL, 0);
    if (pMem_B0 == (int *)-1) {
        printf("Eroare atasare memorie partajata pentru B0\n");
        return 1;
    }

    // Create shared memory for B1
    memID_B1 = shmget(KEY_B1, MEM_SIZE, IPC_CREAT | 0666);
    if (memID_B1 == -1) {
        printf("Eroare creare memorie partajata pentru B1\n");
        return 1;
    }

    pMem_B1 = (int *)shmat(memID_B1, NULL, 0);

    // Process numbers from B0
    while (1) {
        int value = *pMem_B0;
        if (value == 0) {
            *pMem_B1 = 0;
            break;
        }
        if (value % 2 != 0) {
            *pMem_B1 = value;
        }
        sleep(1);
    }
}

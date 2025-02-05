#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> // for sleep

#define KEY_B1 4567
#define MEM_SIZE sizeof(int)

int main() {
    int memID_B1;
    int *pMem_B1;

    memID_B1 = shmget(KEY_B1, MEM_SIZE, 0666);
    pMem_B1 = (int *)shmat(memID_B1, NULL, 0);

    while (*pMem_B1 != 0) {
        if (*pMem_B1 % 3 != 0) {
            printf("%d\n", *pMem_B1);
        }
    }
}

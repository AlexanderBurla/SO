#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key_B0 = 1234, key_B1 = 5678;
    int shmid_B0 = shmget(key_B0, sizeof(int), 0666);
    int shmid_B1 = shmget(key_B1, sizeof(int), IPC_CREAT | 0666);

    if (shmid_B0 == -1 || shmid_B1 == -1) {
        perror("shmget failed");
        return 1;
    }

    int *B0 = (int *)shmat(shmid_B0, NULL, 0);
    int *B1 = (int *)shmat(shmid_B1, NULL, 0);
    if (B0 == (int *)-1 || B1 == (int *)-1) {
        perror("shmat failed");
        return 1;
    }

    while (1) {
        if (*B0 == 0) { // Verifică terminarea
            *B1 = 0;
            break;
        }

        if (*B0 % 2 != 0) {
            *B1 = *B0;
            sleep(1);
        }
    }

    shmdt(B0);
    shmdt(B1);
    return 0;
}

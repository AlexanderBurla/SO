#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    int *B0 = (int *)shmat(shmid, NULL, 0);
    if (B0 == (int *)-1) {
        perror("shmat failed");
        return 1;
    }

    for (int i = 1; i <= 1000; i++) {
        *B0 = i;
        sleep(1);
    }

    *B0 = 0; // Semnalizează terminarea
    shmdt(B0);
    return 0;
}

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key_B1 = 5678;
    int shmid_B1 = shmget(key_B1, sizeof(int), 0666);
    if (shmid_B1 == -1) {
        perror("shmget failed");
        return 1;
    }

    int *B1 = (int *)shmat(shmid_B1, NULL, 0);
    if (B1 == (int *)-1) {
        perror("shmat failed");
        return 1;
    }

    while (1) {
        if (*B1 == 0) { // Verifică terminarea
            break;
        }

        if (*B1 % 3 != 0) {
            printf("Număr afișat: %d\n", *B1);
            sleep(1);
        }
    }

    shmdt(B1);
    shmctl(shmid_B1, IPC_RMID, NULL); // Șterge memoria partajată
    return 0;
}

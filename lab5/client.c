#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    key_t key = 1230;
    int shmid = shmget(key, 1024, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    char *shared_mem = (char *)shmat(shmid, NULL, 0);
    if (shared_mem == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    while (1) {
        printf("Mesaj citit: %s\n", shared_mem);

        if (strcmp(shared_mem, "STOP") == 0) {
            break;
        }
        sleep(1);
    }

    shmdt(shared_mem);
    return 0;
}

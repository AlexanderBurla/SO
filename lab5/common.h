#ifndef COMMON_H
#define COMMON_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define B0_KEY 1234
#define B1_KEY 5678
#define SEM_B0_KEY 1111
#define SEM_B1_KEY 2222

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_op(int semid, int sem_num, int op) {
    struct sembuf sb = {sem_num, op, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("Semaphore operation failed");
        exit(1);
    }
}

#endif

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define DIM_BUFFER 5
#define SHM_NAME "/shm_buffer"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SEM_MUTEX "/sem_mutex"

int main() {
    int *buffer, *in, *out;
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    buffer = mmap(0, (DIM_BUFFER + 2) * sizeof(int), PROT_READ, MAP_SHARED, shm_fd, 0);
    in = &buffer[DIM_BUFFER];
    out = &buffer[DIM_BUFFER + 1];

    sem_t *empty = sem_open(SEM_EMPTY, 0);
    sem_t *full = sem_open(SEM_FULL, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, 0);

    while (1) {
        sem_wait(full);
        sem_wait(mutex);

        int item = buffer[*out];
        printf("Consumator: a consumat %d de la indexul %d\n", item, *out);
        *out = (*out + 1) % DIM_BUFFER;

        sem_post(mutex);
        sem_post(empty);

        sleep(1);
    }

    return 0;
}

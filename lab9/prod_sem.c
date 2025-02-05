#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#define DIM_BUFFER 5
#define SHM_NAME "/shm_buffer"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SEM_MUTEX "/sem_mutex"

int main() {
    int *buffer, *in, *out;
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, (DIM_BUFFER + 2) * sizeof(int));
    buffer = mmap(0, (DIM_BUFFER + 2) * sizeof(int), PROT_WRITE, MAP_SHARED, shm_fd, 0);
    in = &buffer[DIM_BUFFER];
    out = &buffer[DIM_BUFFER + 1];
    *in = 0;
    *out = 0;

    sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, DIM_BUFFER);
    sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    srand(time(NULL));

    while (1) {
        int item = rand() % 100;  // Generează un număr aleator.
        sem_wait(empty);
        sem_wait(mutex);

        buffer[*in] = item;
        printf("Producător: a produs %d la indexul %d\n", item, *in);
        *in = (*in + 1) % DIM_BUFFER;

        sem_post(mutex);
        sem_post(full);

        sleep(1);
    }

    return 0;
}
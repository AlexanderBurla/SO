#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define LIMIT 10

// Variabila globală
int global_var = 0;

// Mutex pentru sincronizarea accesului la variabilă
pthread_mutex_t mutex;

// Funcția pentru primul thread (incrementare)
void *increment_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex); // Blocare mutex
        if (global_var >= LIMIT || global_var <= -LIMIT) {
            pthread_mutex_unlock(&mutex); // Deblocare mutex
            break;
        }
        global_var++;
        printf("Increment thread: global_var = %d\n", global_var);
        pthread_mutex_unlock(&mutex); // Deblocare mutex
        sleep(2);
    }
    return NULL;
}

// Funcția pentru al doilea thread (decrementare)
void *decrement_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex); // Blocare mutex
        if (global_var >= LIMIT || global_var <= -LIMIT) {
            pthread_mutex_unlock(&mutex); // Deblocare mutex
            break;
        }
        printf("Decrement thread: global_var = %d\n", global_var);
        global_var--;
        pthread_mutex_unlock(&mutex); // Deblocare mutex
        sleep(4);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Inițializare mutex
    pthread_mutex_init(&mutex, NULL);

    // Creare thread-uri
    pthread_create(&thread1, NULL, increment_thread, NULL);
    pthread_create(&thread2, NULL, decrement_thread, NULL);

    // Așteptare thread-uri
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Distrugere mutex
    pthread_mutex_destroy(&mutex);

    printf("Programul s-a terminat. Valoarea finală a variabilei: %d\n", global_var);
    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Limitele de incrementare/decrementare
#define LIMIT 10

// Variabila globală
int global_var = 0;

// Mutex pentru sincronizarea accesului
pthread_mutex_t mutex;

// Flag pentru terminarea thread-urilor
int stop_threads = 0;

// Funcția pentru primul thread (incrementare)
void *increment_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Verifică dacă trebuie să oprească thread-urile
        if (stop_threads) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Incrementare
        global_var++;
        printf("Increment thread: global_var = %d\n", global_var);

        // Verifică dacă s-a atins limita
        if (global_var >= LIMIT || global_var <= -LIMIT) {
            stop_threads = 1;
        }

        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}

// Funcția pentru al doilea thread (decrementare)
void *decrement_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Verifică dacă trebuie să oprească thread-urile
        if (stop_threads) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Decrementare
        global_var--;
        printf("Decrement thread: global_var = %d\n", global_var);

        // Verifică dacă s-a atins limita
        if (global_var >= LIMIT || global_var <= -LIMIT) {
            stop_threads = 1;
        }

        pthread_mutex_unlock(&mutex);
        sleep(4);
    }
    return NULL;
}

// Funcția pentru al treilea thread (afișare)
void *display_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Verifică dacă trebuie să oprească thread-urile
        if (stop_threads) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Afișare
        printf("Display thread: global_var = %d\n", global_var);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Inițializare mutex
    pthread_mutex_init(&mutex, NULL);

    // Creare thread-uri
    pthread_create(&thread1, NULL, increment_thread, NULL);
    pthread_create(&thread2, NULL, decrement_thread, NULL);
    pthread_create(&thread3, NULL, display_thread, NULL);

    // Așteptare thread-uri
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Distrugere mutex
    pthread_mutex_destroy(&mutex);

    printf("Programul s-a terminat. Valoarea finală a variabilei: %d\n", global_var);
    return 0;
}

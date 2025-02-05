#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define DimBuffer 5 // Dimensiunea buffer-ului

int buffer[DimBuffer];   // Buffer global
int in = 0;              // Index pentru producător
int out = 0;             // Index pentru consumator
sem_t empty, full, mutex; // Semafoare pentru sincronizare

// Funcția firului producător
void *producer(void *arg) {
    for (int i = 0; i < 20; i++) { // Producem 20 de elemente pentru test
        int item = rand() % 100;  // Valoare aleatorie
        sem_wait(&empty);         // Așteaptă locuri libere în buffer
        sem_wait(&mutex);         // Acces exclusiv la buffer

        // Adăugare element în buffer
        buffer[in] = item;
        printf("Producător: a produs %d la poziția %d\n", item, in);
        in = (in + 1) % DimBuffer; // Incrementare circulară

        sem_post(&mutex);         // Eliberează accesul exclusiv
        sem_post(&full);          // Notifică existența unui element în buffer
        sleep(1);                 // Pauză de 1 secundă
    }
    pthread_exit(NULL);
}

// Funcția firului consumator
void *consumer(void *arg) {
    for (int i = 0; i < 20; i++) { // Consumăm 20 de elemente pentru test
        sem_wait(&full);          // Așteaptă existența unui element în buffer
        sem_wait(&mutex);         // Acces exclusiv la buffer

        // Consumare element din buffer
        int item = buffer[out];
        printf("Consumator: a consumat %d de la poziția %d\n", item, out);
        out = (out + 1) % DimBuffer; // Incrementare circulară

        sem_post(&mutex);         // Eliberează accesul exclusiv
        sem_post(&empty);         // Notifică existența unui loc gol în buffer
        sleep(1);                 // Pauză de 1 secundă
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod_thread, cons_thread; // Fire pentru producător și consumator

    // Inițializare semafoare
    sem_init(&empty, 0, DimBuffer); // Inițializare cu dimensiunea buffer-ului
    sem_init(&full, 0, 0);          // Inițializare cu 0 elemente
    sem_init(&mutex, 0, 1);         // Mutex pentru acces exclusiv

    // Creare fire
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Așteptare terminare fire
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Eliberare semafoare
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

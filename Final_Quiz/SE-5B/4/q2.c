#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_A, sem_B;

void* thread_A(void* arg) {
    sem_wait(&sem_A); // Wait for signal from B
    printf("Thread A is executing.\n");
    return NULL;
}

void* thread_B(void* arg) {
    sem_wait(&sem_B); // Wait for signal from C
    printf("Thread B is executing.\n");
    sem_post(&sem_A); // Signal to A
    return NULL;
}

void* thread_C(void* arg) {
    printf("Thread C is executing.\n");
    sem_post(&sem_B); // Signal to B
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    sem_init(&sem_A, 0, 0);
    sem_init(&sem_B, 0, 0);

    pthread_create(&thread3, NULL, thread_C, NULL);
    pthread_create(&thread2, NULL, thread_B, NULL);
    pthread_create(&thread1, NULL, thread_A, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    sem_destroy(&sem_A);
    sem_destroy(&sem_B);

    return 0;
}

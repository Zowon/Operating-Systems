#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* thread_function(void* arg) {
    long thread_id = (long)arg;
    sem_wait(&semaphore); // Lock the semaphore
    printf("Thread %ld is entering the critical section.\n", thread_id);
    sleep(1); // Simulate work
    printf("Thread %ld is leaving the critical section.\n", thread_id);
    sem_post(&semaphore); // Unlock the semaphore
    return NULL;
}

int main() {
    pthread_t threads[3];
    sem_init(&semaphore, 0, 1); // Initialize semaphore with value 1 (binary)

    for (long i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore); // Cleanup
    return 0;
}


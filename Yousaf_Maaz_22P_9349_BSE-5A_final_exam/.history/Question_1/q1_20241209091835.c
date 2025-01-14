#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t semaphore;

void *thread1function(void *arg)
{
    printf(": Waiting for signal...\n");
    sem_wait(&semaphore); 
    printf("Thread 1: Received signal, proceeding...\n");
    return NULL;
}

void *thread2function(void *arg)
{
    sleep(1); 
    printf("Thread 2: Sending signal...\n");
    sem_post(&semaphore); // Signal to thread 1
    return NULL;
}

void *thread2function(void *arg)
{
    sleep(1); 
    printf("Thread 2: Sending signal...\n");
    sem_post(&semaphore); // Signal to thread 1
    return NULL;
}

void *thread2function(void *arg)
{
    sleep(1); 
    printf("Thread 2: Sending signal...\n");
    sem_post(&semaphore); // Signal to thread 1
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    sem_init(&semaphore, 0, 0); 
    pthread_create(&thread1, NULL, thread1function, NULL);
    pthread_create(&thread2, NULL, thread2function, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore); 
    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t semaphore;

void *thread1function(void *arg)
{
    printf("Thermostats: starting...Intializing...\n");
    sem_wait(&semaphore); 

    printf("Appliances: starting...Intializing...\n");
    sem_wait(&semaphore); 

    printf("lights: starting...Intializing...\n");
    sem_wait(&semaphore); 

    printf("Security: starting...Intializing...\n");
    sem_wait(&semaphore); 
    
    return NULL;
}

void *thread2function(void *arg)
{
    sleep(5); 
    printf("Thermostats: updated status...(5 seconds)\n");
    sem_post(&semaphore); // Signal to thread 1
    sleep(3); 
    printf("Appliances updated status...(3 seconds)\n");
    sem_post(&semaphore); // Signal to thread 1
    

    sleep(2); 
    printf("lights updated status...(2 seconds)\n");
    sem_post(&semaphore); // Signal to thread 1

    printf("security updated status...(6 seconds)\n");
    sem_post(&semaphore); // Signal to thread 1
    return NULL;
}

// void *thread2function(void *arg)
// {
//     sleep(1); 
//     printf("Thread 2: starting...Intializing...\n");
//     sem_post(&semaphore); // Signal to thread 1
//     return NULL;
// }

// void *thread2function(void *arg)
// {
//     sleep(1); 
//     printf("Thread 2: starting...Intializing...\n");
//     sem_post(&semaphore); // Signal to thread 1
//     return NULL;
// }

int main()
{
    pthread_t thread1, thread2 ,thread3 ,thread4;
    sem_init(&semaphore, 0, 0); 
    pthread_create(&thread1, NULL, thread1function, NULL);
    pthread_create(&thread2, NULL, thread2function, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore); 
    return 0;
}

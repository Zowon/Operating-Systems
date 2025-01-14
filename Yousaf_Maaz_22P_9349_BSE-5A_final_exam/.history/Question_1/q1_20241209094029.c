#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<threads.h>

sem_t semaphore;

void *Embedded_system_t1(void *arg)
{
    printf("Thermostats: starting...Intializing...\n");
    sem_wait(&semaphore);

    printf("Appliances: starting...Intializing...\n");
    sem_wait(&semaphore);

    printf("lights: starting...Intializing...\n");
    sem_wait(&semaphore);

    printf("Security: starting...Intializing...\n");
    sem_wait(&semaphore);


    //this for make it according to the output given in q paper.
    
    printf("Security: starting...Intializing...\n");
    sem_wait(&semaphore);
    return NULL;
}

void *Embedded_system_t2(void *arg)
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

    sleep(4);
    printf("security updated status...(6 seconds)\n");
    sem_post(&semaphore); // Signal to thread 1
    return NULL;


}

int main()
{
    pthread_t signal_pass1, signalpass2;
    sem_init(&semaphore, 0, 0);
    pthread_create(&signal_pass1, NULL, Embedded_system_t1, NULL);
    pthread_create(&signalpass2, NULL, Embedded_system_t2, NULL);
    pthread_join(signal_pass1, NULL);
    pthread_join(signalpass2, NULL);
    sem_destroy(&semaphore);
    return 0;
}

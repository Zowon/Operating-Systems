#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


sem_t semaphore;

void *thread_function(void *arg)
{
    sem_wait(&semaphore); // "Locks" the sema phore, de cre asing cou nt by 1
    printf("Thread %ld is entering the critical section.\n", (long)arg);
    // Simulate some work
    sleep(1);
    printf("Thread %ld is leaving the critical section.\n", (long)arg);
    sem_post(&semaphore); // "Unlo cks" the sem ap  hore, inc rea sing co unt by 1
    return NULL;
}

int main()
{
    pthread_t threads[3];
    sem_init(&semaphore, 0, 1); // Init ialize se maphore wi th 1 (binary)

    for (long i = 0; i < 3; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, (void *)i);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore); // Cleanup
    return 0;
}

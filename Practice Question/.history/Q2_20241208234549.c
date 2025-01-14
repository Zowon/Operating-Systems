











#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_VENUES 3

// Shared Data
int venue_status[NUM_VENUES] = {0}; // 0: Available, 1: In Use
sem_t mutex;

// Thread Functions
void* allocate_venue(void* arg) {
    int venue = *((int*)arg);
    sem_wait(&mutex);
    if (venue_status[venue] == 0) {
        printf("Venue %d allocated to a competition.\n", venue + 1);
        venue_status[venue] = 1; // Mark as in use
    } else {
        printf("Venue %d is already in use.\n", venue + 1);
    }
    sem_post(&mutex);
    return NULL;
}

void* monitor_competition(void* arg) {
    int venue = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        sem_wait(&mutex);
        if (venue_status[venue] == 1) {
            printf("Monitoring Venue %d: Competition in progress...\n", venue + 1);
        } else {
            printf("Monitoring Venue %d: No competition.\n", venue + 1);
        }
        sem_post(&mutex);
        sleep(2);
    }
    return NULL;
}

void* resource_utilization(void* arg) {
    int venue = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        sem_wait(&mutex);
        printf("Resource check for Venue %d: All resources functional.\n", venue + 1);
        sem_post(&mutex);
        sleep(3);
    }
    return NULL;
}

int main() {
    pthread_t alloc_threads[NUM_VENUES], monitor_threads[NUM_VENUES], resource_threads[NUM_VENUES];
    int venue_ids[NUM_VENUES] = {0, 1, 2};

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_VENUES; i++) {
        pthread_create(&alloc_threads[i], NULL, allocate_venue, &venue_ids[i]);
        pthread_create(&monitor_threads[i], NULL, monitor_competition, &venue_ids[i]);
        pthread_create(&resource_threads[i], NULL, resource_utilization, &venue_ids[i]);
    }

    for (int i = 0; i < NUM_VENUES; i++) {
        pthread_join(alloc_threads[i], NULL);
        pthread_join(monitor_threads[i], NULL);
        pthread_join(resource_threads[i], NULL);
    }

    sem_destroy(&mutex);
    return 0;
}

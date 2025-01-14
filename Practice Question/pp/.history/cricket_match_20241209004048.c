#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Question: Simulate a cricket match with 6 overs using threads and avoid race conditions.

struct player {
    int p_score;
    int p_out;
};

int score = 0;
int no_of_deliveries = 0;
pthread_mutex_t lock;

void *batsman(void *arg) {
    struct player *p = (struct player *)arg;
    while (no_of_deliveries < 36) {
        pthread_mutex_lock(&lock);

        if (no_of_deliveries >= 36) {
            pthread_mutex_unlock(&lock);
            break;
        }

        int runs = rand() % 7;
        no_of_deliveries++;
        if (runs == 0) {
            p->p_out++;
            score -= 10;
            printf("[Player %p] 0 run(s) - OUT! in %.1f overs\n", p, no_of_deliveries / 6.0);
        } else {
            p->p_score += runs;
            score += runs;
            printf("[Player %p] %d run(s) in %.1f overs\n", p, runs, no_of_deliveries / 6.0);
        }

        pthread_mutex_unlock(&lock);
        usleep(50000); // Simulate time for next ball
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t player1, player2;
    struct player p1 = {0, 0}, p2 = {0, 0};

    pthread_mutex_init(&lock, NULL);

    pthread_create(&player1, NULL, batsman, &p1);
    pthread_create(&player2, NULL, batsman, &p2);

    pthread_join(player1, NULL);
    pthread_join(player2, NULL);

    printf("Total Score: %d in %.1f overs\n", score, no_of_deliveries / 6.0);
    printf("[Batsman 1] Score: %d Got out %d times\n", p1.p_score, p1.p_out);
    printf("[Batsman 2] Score: %d Got out %d times\n", p2.p_score, p2.p_out);

    pthread_mutex_destroy(&lock);

    return 0;
}

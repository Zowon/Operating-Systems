
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <string.h>

// Mutex for thread synchronization
pthread_mutex_t mutex;

// Semaphore for binary counting
sem_t sem_binary, sem_counting;

// Function to demonstrate fork()
void demo_fork() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process (PID: %d)\n", getpid());
        exit(0);
    } else {
        wait(NULL);
        printf("Parent process (PID: %d)\n", getpid());
    }
}

// Thread function for demonstration
void* thread_function(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread %d is running\n", *(int*)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Function to demonstrate threads
void demo_threads() {
    pthread_t thread1, thread2;
    int thread_id1 = 1, thread_id2 = 2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, thread_function, &thread_id1);
    pthread_create(&thread2, NULL, thread_function, &thread_id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);
}

// Signal handler function
void signal_handler(int sig) {
    printf("Caught signal %d\n", sig);
}

// Function to demonstrate signal handling
void demo_signal_handling() {
    signal(SIGINT, signal_handler);
    printf("Press Ctrl+C to test signal handling\n");
    sleep(5); // Allow time to test
}

// Function to demonstrate pipes
void demo_pipes() {
    int fd[2];
    char buffer[50];

    if (pipe(fd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        close(fd[0]); // Close reading end in child
        char* msg = "Hello from child";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
        exit(0);
    } else {
        close(fd[1]); // Close writing end in parent
        read(fd[0], buffer, sizeof(buffer));
        close(fd[0]);
        printf("Parent received: %s\n", buffer);
        wait(NULL);
    }
}

// Function to demonstrate semaphores
void demo_semaphores() {
    sem_init(&sem_binary, 0, 1); // Binary semaphore
    sem_init(&sem_counting, 0, 3); // Counting semaphore

    printf("Binary semaphore acquired\n");
    sem_wait(&sem_binary);
    printf("Binary semaphore released\n");
    sem_post(&sem_binary);

    printf("Counting semaphore acquired\n");
    for (int i = 0; i < 3; ++i) {
        sem_wait(&sem_counting);
        printf("Resource %d acquired\n", i + 1);
    }
    for (int i = 0; i < 3; ++i) {
        sem_post(&sem_counting);
        printf("Resource %d released\n", i + 1);
    }

    sem_destroy(&sem_binary);
    sem_destroy(&sem_counting);
}

// Main function
int main() {
    printf("1. Fork() demonstration:\n");
    demo_fork();

    printf("\n2. Threads demonstration:\n");
    demo_threads();

    printf("\n3. Signal handling demonstration:\n");
    demo_signal_handling();

    printf("\n4. Pipes demonstration:\n");
    demo_pipes();

    printf("\n5. Semaphores demonstration:\n");
    demo_semaphores();

    printf("\nAll demonstrations completed.\n");
    return 0;
}

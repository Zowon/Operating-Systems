#include <stdio.h>
#include <unistd.h>
#include <
// Question: Write a process tree with the structure mentioned in the question.
// Explanation: Using fork() multiple times for creating required child processes.

int main() {
    pid_t pid1, pid2;

    // Create P1
    pid1 = fork();
    if (pid1 == 0) {
        // Create P2
        pid2 = fork();
        if (pid2 == 0) {
            printf("P2: PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            printf("P1: PID = %d, Parent PID = %d\n", getpid(), getppid());
        }
    } else {
        printf("Parent: PID = %d\n", getpid());
    }

    return 0;
}

// Preferred Strategy: Combining if-else with specific conditions for better process creation.
// Reason: It provides structured and predictable results for hierarchical process creation.

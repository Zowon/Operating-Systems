#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void create_process(const char* name) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Process %s created with PID: %d, Parent PID: %d\n", name, getpid(), getppid());
    } else if (pid > 0) {
        // Parent process waits
        wait(NULL);
    }
}

int main() {
    printf("Parent Process (Event Manager) PID: %d\n", getpid());

    // Create child processes
    create_process("Registration Coordinator");
    create_process("Scheduling Coordinator");

    if (fork() == 0) {
        // Scheduling Coordinator's children
        create_process("Venue Allocation");
        create_process("Time Management");
        _exit(0);
    }

    create_process("Broadcast Coordinator");

    return 0;
}

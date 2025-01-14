// Question 4: Process Tree for Event Coordination (10 Marks)
// Create a Process Tree to represent the coordination hierarchy for the NUTEC event. The tree should consist of:
// Parent Process (Event Manager): Responsible for creating and monitoring child processes.
// Child 1 (Registration Coordinator): Manages the registration process for the event.
// Child 2 (Scheduling Coordinator): Manages scheduling for competitions.
// Child 2.1 (Venue Allocation): Allocates venues for each competition.
// Child 2.2 (Time Management): Assigns time slots for each competition.
// Child 3 (Broadcast Coordinator): Manages event announcements and notifications.
// Requirements:
// Use fork() to create the processes as per the tree structure.
// Display the Process IDs (PIDs) of each process and their relationship (Parent/Child).
// Bonus:
// Add functionality to terminate all child processes gracefully when the parent process exits.






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

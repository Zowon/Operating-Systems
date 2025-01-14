#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a task
typedef struct
{
    char name[10]; // Name of the task
    int priority;  // Priority of the task (lower value = higher priority)
    int cpuBurst;  // CPU Burst Time (execution time required)
} Task;

// Function prototypes for different scheduling algorithms
void fcfs(Task tasks[], int n);                                    // First Come, First Serve
void sjf(Task tasks[], int n);                                     // Shortest Job First
void priorityScheduling(Task tasks[], int n);                      // Priority Scheduling
void roundRobin(Task tasks[], int n, int timeQuantum);             // Round Robin
void priorityWithRoundRobin(Task tasks[], int n, int timeQuantum); // Priority + Round Robin

// Main function
int main()
{
    // Open the input file containing task details
    FILE *file = fopen("schedule.txt", "r");
    if (!file) // Check if the file opened successfully
    {
        printf("Error: Could not open schedule.txt.\n");
        return 1; // Exit the program if the file could not be opened
    }

    // Read tasks from the file
    Task tasks[100]; // Array to store up to 100 tasks
    int count = 0;   // Variable to count the number of tasks
    while (fscanf(file, "%[^,], %d, %d\n", tasks[count].name, &tasks[count].priority, &tasks[count].cpuBurst) != EOF)
    {
        count++; // Increment task count after reading each line
    }
    fclose(file); // Close the file after reading

    int choice, timeQuantum; // Variables for user input
    // Display menu options for CPU scheduling algorithms
    printf("CPU Scheduling Algorithms\n");
    printf("1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. Priority with Round Robin\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice); // Take user's choice as input

    // Execute the chosen scheduling algorithm
    switch (choice)
    {
    case 1: // First Come, First Serve
        fcfs(tasks, count);
        break;
    case 2: // Shortest Job First
        sjf(tasks, count);
        break;
    case 3: // Priority Scheduling
        priorityScheduling(tasks, count);
        break;
    case 4: // Round Robin
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &timeQuantum);
        roundRobin(tasks, count, timeQuantum);
        break;
    case 5: // Priority with Round Robin
        printf("Enter time quantum for Priority with Round Robin: ");
        scanf("%d", &timeQuantum);
        priorityWithRoundRobin(tasks, count, timeQuantum);
        break;
    default: // Invalid choice
        printf("Invalid choice.\n");
        break;
    }

    return 0; // End of program
}

// FCFS (First Come, First Serve) implementation
void fcfs(Task tasks[], int n)
{
    printf("Task Execution Order (FCFS):\n");
    // Tasks are executed in the order they appear
    for (int i = 0; i < n; i++)
    {
        printf("Task: %s, Priority: %d, CPU Burst Time: %d\n",
               tasks[i].name, tasks[i].priority, tasks[i].cpuBurst);
    }
}

// SJF (Shortest Job First) implementation
void sjf(Task tasks[], int n)
{
    // Sort tasks by CPU Burst Time (ascending order)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tasks[j].cpuBurst > tasks[j + 1].cpuBurst)
            {
                Task temp = tasks[j]; // Swap tasks
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    // Print tasks after sorting
    printf("Task Execution Order (SJF):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Task: %s, Priority: %d, CPU Burst Time: %d\n",
               tasks[i].name, tasks[i].priority, tasks[i].cpuBurst);
    }
}

// Priority Scheduling implementation
void priorityScheduling(Task tasks[], int n)
{
    // Sort tasks by Priority (ascending order, lower value = higher priority)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tasks[j].priority > tasks[j + 1].priority)
            {
                Task temp = tasks[j]; // Swap tasks
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    // Print tasks after sorting
    printf("Task Execution Order (Priority Scheduling):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Task: %s, Priority: %d, CPU Burst Time: %d\n",
               tasks[i].name, tasks[i].priority, tasks[i].cpuBurst);
    }
}

// Round Robin implementation
void roundRobin(Task tasks[], int n, int timeQuantum)
{
    int remainingBurst[n]; // Array to track remaining burst time for each task
    for (int i = 0; i < n; i++)
    {
        remainingBurst[i] = tasks[i].cpuBurst; // Initialize remaining burst times
    }

    int time = 0; // Keep track of total execution time
    printf("Task Execution Order (Round Robin):\n");
    while (1) // Continue until all tasks are completed
    {
        int done = 1; // Flag to check if all tasks are done
        for (int i = 0; i < n; i++)
        {
            if (remainingBurst[i] > 0) // If task is not yet completed
            {
                done = 0; // Mark as not done
                if (remainingBurst[i] > timeQuantum)
                {
                    time += timeQuantum;
                    remainingBurst[i] -= timeQuantum;
                    printf("Task: %s executed for %d units.\n", tasks[i].name, timeQuantum);
                }
                else
                {
                    time += remainingBurst[i];
                    printf("Task: %s executed for %d units.\n", tasks[i].name, remainingBurst[i]);
                    remainingBurst[i] = 0; // Mark task as completed
                }
            }
        }
        if (done) // Exit loop if all tasks are completed
            break;
    }
    printf("Total Time: %d\n", time); // Print total execution time
}

// Priority with Round Robin implementation
void priorityWithRoundRobin(Task tasks[], int n, int timeQuantum)
{
    // Sort tasks by priority first
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tasks[j].priority > tasks[j + 1].priority)
            {
                Task temp = tasks[j]; // Swap tasks
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    // Apply Round Robin on sorted tasks
    int remainingBurst[n]; // Track remaining burst times
    for (int i = 0; i < n; i++)
    {
        remainingBurst[i] = tasks[i].cpuBurst;
    }

    int time = 0; // Track total execution time
    printf("Task Execution Order (Priority with Round Robin):\n");
    while (1) // Continue until all tasks are completed
    {
        int done = 1; // Flag to check if all tasks are done
        for (int i = 0; i < n; i++)
        {
            if (remainingBurst[i] > 0) // If task is not yet completed
            {
                done = 0; // Mark as not done
                if (remainingBurst[i] > timeQuantum)
                {
                    time += timeQuantum;
                    remainingBurst[i] -= timeQuantum;
                    printf("Task: %s executed for %d units (Priority: %d).\n",
                           tasks[i].name, timeQuantum, tasks[i].priority);
                }
                else
                {
                    time += remainingBurst[i];
                    printf("Task: %s executed for %d units (Priority: %d).\n",
                           tasks[i].name, remainingBurst[i], tasks[i].priority);
                    remainingBurst[i] = 0; // Mark task as completed
                }
            }
        }
        if (done) // Exit loop if all tasks are completed
            break;
    }
    printf("Total Time: %d\n", time); // Print total execution time
}

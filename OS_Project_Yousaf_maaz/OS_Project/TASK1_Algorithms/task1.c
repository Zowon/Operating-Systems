#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[10];
    int priority;
    int cpuBurst;
} Task;

// Function prototypes
void fcfs(Task tasks[], int n);
void sjf(Task tasks[], int n);
void priorityScheduling(Task tasks[], int n);
void roundRobin(Task tasks[], int n, int timeQuantum);
void priorityWithRoundRobin(Task tasks[], int n, int timeQuantum);

// Main function
int main()
{
    FILE *file = fopen("schedule.txt", "r");
    if (!file)
    {
        printf("Error: Could not open schedule.txt.\n");
        return 1;
    }

    Task tasks[100];
    int count = 0;
    while (fscanf(file, "%[^,], %d, %d\n", tasks[count].name, &tasks[count].priority, &tasks[count].cpuBurst) != EOF)
    {
        count++;
    }
    fclose(file);

    int choice, timeQuantum;
    printf("CPU Scheduling Algorithms\n");
    printf("1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. Priority with Round Robin\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        fcfs(tasks, count);
        break;
    case 2:
        sjf(tasks, count);
        break;
    case 3:
        priorityScheduling(tasks, count);
        break;
    case 4:
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &timeQuantum);
        roundRobin(tasks, count, timeQuantum);
        break;
    case 5:
        printf("Enter time quantum for Priority with Round Robin: ");
        scanf("%d", &timeQuantum);
        priorityWithRoundRobin(tasks, count, timeQuantum);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }

    return 0;
}

// FCFS implementation
void fcfs(Task tasks[], int n)
{
    printf("Task Execution Order (FCFS):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Task: %s, Priority: %d, CPU Burst Time: %d\n",
               tasks[i].name, tasks[i].priority, tasks[i].cpuBurst);
    }
}

// SJF implementation
void sjf(Task tasks[], int n)
{
    // Sort tasks by CPU Burst Time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tasks[j].cpuBurst > tasks[j + 1].cpuBurst)
            {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

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
    // Sort tasks by Priority
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tasks[j].priority > tasks[j + 1].priority)
            {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

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
    int remainingBurst[n];
    for (int i = 0; i < n; i++)
    {
        remainingBurst[i] = tasks[i].cpuBurst;
    }

    int time = 0;
    printf("Task Execution Order (Round Robin):\n");
    while (1)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (remainingBurst[i] > 0)
            {
                done = 0;
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
                    remainingBurst[i] = 0;
                }
            }
        }
        if (done)
            break;
    }
    printf("Total Time: %d\n", time);
}

// Priority with Round Robin implementation
void priorityWithRoundRobin(Task tasks[], int n, int timeQuantum)
{
    // Sort by priority first
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tasks[j].priority > tasks[j + 1].priority)
            {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    // Apply Round Robin on sorted tasks
    int remainingBurst[n];
    for (int i = 0; i < n; i++)
    {
        remainingBurst[i] = tasks[i].cpuBurst;
    }

    int time = 0;
    printf("Task Execution Order (Priority with Round Robin):\n");
    while (1)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (remainingBurst[i] > 0)
            {
                done = 0;
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
                    remainingBurst[i] = 0;
                }
            }
        }
        if (done)
            break;
    }
    printf("Total Time: %d\n", time);
}

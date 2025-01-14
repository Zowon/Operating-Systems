#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Task structure
typedef struct
{
    char name[10];
    int priority;
    int cpuBurst;
    int remainingBurst; // For Round Robin
} Task;

// Function prototypes
void sortTasks(Task tasks[], int n, char type);
void fcfs(Task tasks[], int n);
void sjf(Task tasks[], int n);
void priorityScheduling(Task tasks[], int n);
void roundRobin(Task tasks[], int n, int timeQuantum);
void priorityWithRoundRobin(Task tasks[], int n, int timeQuantum);
void printGanttChart(char taskNames[][10], int startTimes[], int endTimes[], int len);

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
        tasks[count].remainingBurst = tasks[count].cpuBurst; // Initialize remainingBurst
        count++;
    }
    fclose(file);

    int choice, timeQuantum;
    printf("CPU Scheduling Algorithms\n");
    printf("1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. Priority with Round Robin\n");
    printf("Enter your choice (1-5): ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
    {
        printf("Invalid choice.\n");
        return 1;
    }

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
        if (scanf("%d", &timeQuantum) != 1 || timeQuantum <= 0)
        {
            printf("Invalid time quantum.\n");
            return 1;
        }
        roundRobin(tasks, count, timeQuantum);
        break;
    case 5:
        printf("Enter time quantum for Priority with Round Robin: ");
        if (scanf("%d", &timeQuantum) != 1 || timeQuantum <= 0)
        {
            printf("Invalid time quantum.\n");
            return 1;
        }
        priorityWithRoundRobin(tasks, count, timeQuantum);
        break;
    }

    return 0;
}

// Sort tasks by CPU Burst Time or Priority
void sortTasks(Task tasks[], int n, char type)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int condition = (type == 'B') ? (tasks[j].cpuBurst > tasks[j + 1].cpuBurst)
                                          : (tasks[j].priority > tasks[j + 1].priority);
            if (condition)
            {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

// Print Gantt chart
void printGanttChart(char taskNames[][10], int startTimes[], int endTimes[], int len)
{
    printf("\nGantt Chart:\n");
    for (int i = 0; i < len; i++)
    {
        printf("| %-8s ", taskNames[i]);
    }
    printf("|\n");
    for (int i = 0; i < len; i++)
    {
        printf("%-3d       ", startTimes[i]);
    }
    printf("%-3d\n\n", endTimes[len - 1]);
}

// FCFS implementation
void fcfs(Task tasks[], int n)
{
    printf("Task Execution Order (FCFS):\n");

    char taskNames[n][10];
    int startTimes[n], endTimes[n];
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        strcpy(taskNames[i], tasks[i].name);
        startTimes[i] = currentTime;
        currentTime += tasks[i].cpuBurst;
        endTimes[i] = currentTime;
        printf("Task: %s, Priority: %d, CPU Burst Time: %d\n",
               tasks[i].name, tasks[i].priority, tasks[i].cpuBurst);
    }
    printGanttChart(taskNames, startTimes, endTimes, n);
}

// SJF implementation
void sjf(Task tasks[], int n)
{
    sortTasks(tasks, n, 'B'); // Sort by CPU Burst

    char taskNames[n][10];
    int startTimes[n], endTimes[n];
    int currentTime = 0;

    printf("Task Execution Order (SJF):\n");
    for (int i = 0; i < n; i++)
    {
        strcpy(taskNames[i], tasks[i].name);
        startTimes[i] = currentTime;
        currentTime += tasks[i].cpuBurst;
        endTimes[i] = currentTime;
        printf("Task: %s, Priority: %d, CPU Burst Time: %d\n",
               tasks[i].name, tasks[i].priority, tasks[i].cpuBurst);
    }
    printGanttChart(taskNames, startTimes, endTimes, n);
}

// Priority Scheduling implementation
void priorityScheduling(Task tasks[], int n)
{
    sortTasks(tasks, n, 'P'); // Sort by Priority

    char taskNames[n][10];
    int startTimes[n], endTimes[n];
    int currentTime = 0;

    printf("Task Execution Order (Priority Scheduling):\n");
    for (int i = 0; i < n; i++)
    {
        strcpy(taskNames[i], tasks[i].name);
        startTimes[i] = currentTime;
        currentTime += tasks[i].cpuBurst;
        endTimes[i] = currentTime;
        printf("Task: %s, Priority: %d, CPU Burst Time: %d\n",
               tasks[i].name, tasks[i].priority, tasks[i].cpuBurst);
    }
    printGanttChart(taskNames, startTimes, endTimes, n);
}

// Round Robin implementation
void roundRobin(Task tasks[], int n, int timeQuantum)
{
    char taskNames[100][10];
    int startTimes[100], endTimes[100];
    int idx = 0, time = 0;

    printf("Task Execution Order (Round Robin):\n");
    while (1)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (tasks[i].remainingBurst > 0)
            {
                done = 0;
                startTimes[idx] = time;
                strcpy(taskNames[idx], tasks[i].name);

                int execTime = (tasks[i].remainingBurst > timeQuantum) ? timeQuantum : tasks[i].remainingBurst;
                tasks[i].remainingBurst -= execTime;
                time += execTime;

                endTimes[idx++] = time;
                printf("Task: %s executed for %d units.\n", tasks[i].name, execTime);
            }
        }
        if (done)
            break;
    }
    printGanttChart(taskNames, startTimes, endTimes, idx);
}

// Priority with Round Robin implementation
void priorityWithRoundRobin(Task tasks[], int n, int timeQuantum)
{
    sortTasks(tasks, n, 'P');

    char taskNames[100][10];
    int startTimes[100], endTimes[100];
    int idx = 0, time = 0;

    printf("Task Execution Order (Priority with Round Robin):\n");
    for (int currentPriority = tasks[0].priority; currentPriority <= tasks[n - 1].priority; currentPriority++)
    {
        while (1)
        {
            int executedAnyTask = 0;
            for (int i = 0; i < n; i++)
            {
                if (tasks[i].priority == currentPriority && tasks[i].remainingBurst > 0)
                {
                    executedAnyTask = 1;
                    startTimes[idx] = time;
                    strcpy(taskNames[idx], tasks[i].name);

                    int execTime = (tasks[i].remainingBurst > timeQuantum) ? timeQuantum : tasks[i].remainingBurst;
                    tasks[i].remainingBurst -= execTime;
                    time += execTime;

                    endTimes[idx++] = time;
                    printf("Task: %s executed for %d units (Priority: %d).\n",
                           tasks[i].name, execTime, tasks[i].priority);
                }
            }
            if (!executedAnyTask)
                break;
        }
    }
    printGanttChart(taskNames, startTimes, endTimes, idx);
}

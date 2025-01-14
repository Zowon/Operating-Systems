CPU Scheduling Algorithms Implementation
Overview
This program implements several CPU scheduling algorithms in C. The algorithms simulate how an operating system schedules tasks (or processes) based on various strategies. The tasks are defined in a separate text file (schedule.txt), which the program reads as input.

Why Use a Text File (schedule.txt)?
The schedule.txt file is used to provide input tasks for the scheduling algorithms. Here's why:

Dynamic Input: It allows tasks to be defined and modified without altering the source code.
Ease of Testing: Enables quick testing of different scheduling scenarios by simply editing the file.
Real-world Use Case: Reflects how real systems store job data in files or other external sources.
Separation of Concerns: Keeps input data separate from the program logic for better maintainability.
How to Prepare schedule.txt
The file must follow this format:

Copy code
TaskName, Priority, BurstTime
Example:

Copy code
T1, 4, 20
T2, 2, 25
T3, 3, 25
T4, 3, 15
T5, 10, 10
TaskName: A unique identifier for the task (e.g., T1, T2).
Priority: A numeric value representing the task's priority (lower number = higher priority).
BurstTime: The time required by the task to complete execution.
Implemented Scheduling Algorithms
First-Come-First-Served (FCFS): Executes tasks in the order they appear in the file.
Shortest Job First (SJF): Executes tasks based on their burst time (shortest first).
Priority Scheduling: Executes tasks based on their priority (lower priority value = higher priority).
Round Robin (RR): Executes tasks cyclically using a time quantum.
Priority with Round Robin: Combines priority scheduling with Round Robin for tasks with the same priority.
How to Compile and Run
Step 1: Compile the Program
Run the following command to compile the program:

bash
Copy code
gcc cpu_scheduling.c -o cpu_scheduling
Step 2: Prepare Input File
Ensure the schedule.txt file is in the same directory as the compiled program.

Step 3: Run the Program
Run the program and follow the on-screen instructions:

bash
Copy code
./cpu_scheduling
Step 4: Select a Scheduling Algorithm
When prompted, choose an algorithm from the menu by entering its number (1–5):

1: FCFS
2: SJF
3: Priority Scheduling
4: Round Robin
5: Priority with Round Robin
If you choose Round Robin or Priority with Round Robin, you will be prompted to enter the time quantum.

Sample Output
Example Input (schedule.txt):

Copy code
T1, 4, 20
T2, 2, 25
T3, 3, 25
T4, 3, 15
T5, 10, 10
Example Execution (FCFS):

plaintext
Copy code
Task Execution Order: T1 -> T2 -> T3 -> T4 -> T5
Waiting Times: 0, 20, 45, 70, 85
Turnaround Times: 20, 45, 70, 85, 95
Average Waiting Time: 58.00
Average Turnaround Time: 63.00
Notes
Ensure that the schedule.txt file is properly formatted to avoid errors.
The program will gracefully handle invalid input by displaying an error message.
Contact
For queries or assistance, feel free to reach out:
Author: Yousaf Maaz
Email: yousafmaaz.kakakhel@gmail.com


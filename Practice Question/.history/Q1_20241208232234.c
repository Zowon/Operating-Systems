Question: Distributed Event Management System (20 Marks)
NUTEC at FAST Peshawar is a large-scale event that involves multiple competitions across various domains. To manage this event efficiently, a Distributed Event Management System needs to be designed. This system will consist of multiple processes, each handling a specific aspect of the event. Communication between these processes will be facilitated using pipes, ensuring synchronized and seamless operations.

The system should include the following processes:

Event Registration Process (ER1): Responsible for collecting participant details from a file and forwarding them to the Scheduling Process.
Scheduling Process (ER2): Receives participant details from ER1, assigns competition slots based on participant preferences, and forwards the schedule to the Venue Management Process.
Venue Management Process (ER3): Receives schedules from ER2, maps the competitions to available venues, and sends the finalized schedule to the Broadcasting Process.
Broadcasting Process (ER4): Receives the finalized schedule from ER3 and generates announcements for the event in the form of files.
Requirements:
Use fork() to create the four processes: ER1, ER2, ER3, and ER4.
Ensure pipe communication between the processes for efficient data transfer.
Implement proper synchronization to avoid data inconsistency.
The output should include:
Participant details forwarded by ER1.
Schedules generated by ER2.
Venue assignments by ER3.
Announcements by ER4.
Bonus (Optional):
Implement error handling to ensure that:

Files for participant details or venues are present.
All pipes are closed properly after use.
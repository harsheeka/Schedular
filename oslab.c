#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Process structure
struct Process {
    int pid;
    int burst_time;
    int priority;        // Used for priority scheduling
    int arrival_time;
    int remaining_time;
    int waiting_time;
    int completed;
    int completion_time; // To track completion time
    int turn_around_time; // To track turnaround time
};

// Functions
int areAllProcessesDone(struct Process processes[], int n);
void priorityScheduling(struct Process processes[], int num);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Creation of processes
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Fork failed!\n");
            return 1;
        } else if (pid == 0) { 
            exit(0); 
        } else { 
            // Parent stores the PID and arrival time
            wait(NULL); 
            processes[i].pid = pid; // Storing the child's PID
            printf("Process %d created: PID = %d\n", i + 1, processes[i].pid);

            // Input burst time and arrival time for each process
            printf("Enter burst time for Process %d: ", i + 1);
            scanf("%d", &processes[i].burst_time);
            printf("Enter arrival time for Process %d: ", i + 1);
            scanf("%d", &processes[i].arrival_time);
            processes[i].remaining_time = processes[i].burst_time;
            processes[i].waiting_time = 0;
            processes[i].completed = 0;
            processes[i].completion_time = 0;  // Initialize completion time
            processes[i].turn_around_time = 0; // Initialize turnaround time
        }
    }

    // Choosing the scheduler
    int choice;
    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Round-Robin\n");
    printf("2. Priority-based Scheduling\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Round-Robin Scheduling
        int quantum;
        printf("Round-Robin selected. Enter quantum time: ");
        scanf("%d", &quantum);

        int time = 0;
        int done = 0;

        while (!areAllProcessesDone(processes, n)) {
            done = 1;

            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= time && !processes[i].completed) {
                    if (processes[i].remaining_time > 0) {
                        done = 0;

                        if (processes[i].remaining_time > quantum) {
                            printf("Time %d: Process with PID = %d executed for %d units (Remaining Time = %d).\n",
                                   time, processes[i].pid, quantum, processes[i].remaining_time - quantum);
                            processes[i].remaining_time -= quantum;
                            time += quantum;
                        } else {
                            printf("Time %d: Process with PID = %d executed for %d units (Completed).\n",
                                   time, processes[i].pid, processes[i].remaining_time);
                            time += processes[i].remaining_time;
                            processes[i].remaining_time = 0;
                            processes[i].completed = 1;
                            processes[i].completion_time = time;  // Setingt the completion time
                        }
                    }
                }
            }

            // Increment time if no process is ready
            if (done == 1) {
                time++;
            }
        }

        // Calculation of waiting time
        float total_waiting_time = 0;
        for (int i = 0; i < n; i++) {
            int turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = turnaround_time - processes[i].burst_time;
            total_waiting_time += processes[i].waiting_time;
        }
        printf("Average Waiting Time: %.2f\n", total_waiting_time / n);

    } else if (choice == 2) {
        // Priority-based Scheduling
        printf("Priority-based Scheduling selected.\n");

        // Ask for priority for each process
        for (int i = 0; i < n; i++) {
            printf("Enter priority for Process %d (lower number means higher priority): ", i + 1);
            scanf("%d", &processes[i].priority);
        }

        priorityScheduling(processes, n);

    } else {
        printf("Invalid choice. Exiting...\n");
        exit(1);
    }

    return 0;
}

// Function to check if all processes are done
int areAllProcessesDone(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        if (!processes[i].completed) {
            return 0;
        }
    }
    return 1;
}

// Priority-based Scheduling Function
void priorityScheduling(struct Process processes[], int num) {
    int time = 0;
    int total = 0;
    float average_waiting_time, average_turnaround_time;

    // Sorting processes by priority (lower value means higher priority)
    struct Process temp_process;
    int position;

    for (int i = 0; i < num; i++) {
        position = i;
        for (int j = i + 1; j < num; j++) {
            // Check if priority is higher for swapping (lower value means higher priority)
            if (processes[j].priority < processes[position].priority) {
                position = j;
            }
        }
        // Swapping processes
        temp_process = processes[i];
        processes[i] = processes[position];
        processes[position] = temp_process;
    }

    // Calculate waiting time and turnaround time
    for (int i = 0; i < num; i++) {
        if (i == 0) {
            processes[i].waiting_time = 0; // First process does not wait
        } else {
            processes[i].waiting_time = 0;
            for (int j = 0; j < i; j++) {
                // Calculate waiting time
                processes[i].waiting_time += processes[j].burst_time;
            }
        }

        // Calculate turnaround time
        processes[i].turn_around_time = processes[i].burst_time + processes[i].waiting_time;

        // Calculate total waiting time and turnaround time
        total += processes[i].waiting_time;
    }

    // Average waiting time
    average_waiting_time = (float)total / num;

    // Calculate average turnaround time
    total = 0; // Reset total for turnaround time calculation
    for (int i = 0; i < num; i++) {
        total += processes[i].turn_around_time;
    }
    average_turnaround_time = (float)total / num;

    // Print process details
    printf("\n\nProcess_PID \t Burst Time \t Waiting Time \t Turnaround Time\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < num; i++) {
        printf("\t  %d \t\t  %d \t\t %d \t\t %d\n",
               processes[i].pid,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turn_around_time);
        printf("-----------------------------------------------------------\n");
    }

    // Print average waiting and turnaround times
    printf("\n\nAverage Waiting Time : %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

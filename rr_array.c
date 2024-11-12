#include <stdio.h>

// Define the maximum number of processes
#define MAX_PROCESSES 100

// Structure to hold process details
struct process {
    int pid; // Process ID
    int burst_time; // Burst time of the process
    int remaining_time; // Remaining time of the process
    int waiting_time; // Waiting time of the process
    int turn_around_time; // Turnaround time of the process
    int start_time; // Start time of the process
    int end_time; // End time of the process
};

// Array to hold all processes
struct process processes[100];
int process_count = 0;

// Function to add a process to the array
void add_process(int bt, int i) {
    processes[process_count].pid = i;
    processes[process_count].burst_time = bt;
    processes[process_count].remaining_time = bt;
    processes[process_count].waiting_time = 0;
    processes[process_count].turn_around_time = 0;
    processes[process_count].start_time = 0;
    processes[process_count].end_time = 0;
    process_count++;
}

// Function to perform round robin scheduling
void round_robin(int tq) {
    int done; // Flag to check if all processes are done
    int time = 0; // Current time

    do {
        done = 1;
        for (int i = 0; i < process_count; i++) {
            if (processes[i].remaining_time > 0) {
                done = 0;
                if (processes[i].remaining_time > tq) {
                    processes[i].start_time = time;
                    time += tq;
                    processes[i].remaining_time -= tq;
                    processes[i].end_time = time;
                } else {
                    processes[i].start_time = time;
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].burst_time;
                    processes[i].turn_around_time = time;
                    processes[i].end_time = time;
                    processes[i].remaining_time = 0;
                }
                // Print the start and end time of the current process
                printf("\nPID: %d, Start time: %d, End Time: %d\n", processes[i].pid, processes[i].start_time, processes[i].end_time);
            }
        }
    } while (!done); // Repeat until all processes are done
}

// Function to print the Gantt chart
void gantt_chart() {
    printf("\nGantt Chart\n");
    printf("PID\tBurst Time\tStart Time\tEnd Time\n");
    for (int i = 0; i < process_count; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].start_time, processes[i].end_time);
    }
}

// Function to calculate and print average waiting time and turnaround time
void avg() {
    int wt = 0, tat = 0;

    for (int i = 0; i < process_count; i++) {
        wt += processes[i].waiting_time;
        tat += processes[i].turn_around_time;
    }

    // Print the average waiting time and turnaround time
    printf("Average Waiting Time: %.2f\n", (float)wt / process_count);
    printf("Average Turn Around Time: %.2f\n", (float)tat / process_count);
}

int main() {
    int n, bt, time_quantum;

    // Prompt the user to enter the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Prompt the user to enter the burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &bt);
        add_process(bt, i + 1);
    }

    // Prompt the user to enter the time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Perform round robin scheduling
    round_robin(time_quantum);

    // Print the Gantt chart
    gantt_chart();

    // Print the average waiting time and turnaround time
    avg();

    return 0;
}
#include <stdio.h>

// Structure to represent a process
struct process {
    int pid;               // Process ID
    int burst_time;        // Burst time of the process
    int waiting_time;      // Waiting time of the process
    int turn_around_time;  // Turn around time of the process
};

// Function to calculate the waiting time and turn around time for each process
void calc(struct process proc[], int n) {
    // The first process always has a waiting time of 0
    proc[0].waiting_time = 0;
    // The turn around time for the first process is its burst time
    proc[0].turn_around_time = proc[0].burst_time;

    // Loop through all processes starting from the second one
    for (int i = 1; i < n; i++) {
        // Waiting time of the current process is the sum of the waiting time
        // and burst time of the previous process
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
        // Turn around time is the sum of the waiting time and burst time of the current process
        proc[i].turn_around_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

// Function to display the Gantt chart
void gantt_chart(struct process proc[], int n) {
    printf("\nGantt Chart\n");
    printf("PID\tBurst Time\tWaiting Time\tTurn Around Time\n");
    // Loop through all processes and print their details
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turn_around_time);
    }
}

// Function to calculate and display the average waiting time and turn around time
void avg_time(struct process proc[], int n) {
    int total_wt = 0, total_tat = 0;  // Variables to store total waiting time and turn around time

    // Loop through all processes to sum up the waiting time and turn around time
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turn_around_time;
    }

    // Calculate and print the average waiting time
    printf("Average Waiting Time: %f\n", (float)total_wt / n);
    // Calculate and print the average turn around time
    printf("Average Turn Around Time: %f\n", (float)total_tat / n);
}

int main() {
    int n;  // Variable to store the number of processes

    // Ask the user to enter the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array to store the processes
    struct process proc[100];

    // Loop to get the burst time for each process from the user
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].pid = i + 1;  // Assign a process ID starting from 1
    }

    // Calculate waiting time and turn around time for each process
    calc(proc, n);
    // Display the Gantt chart
    gantt_chart(proc, n);
    // Calculate and display the average waiting time and turn around time
    avg_time(proc, n);

    return 0;  // Indicate that the program ended successfully
}

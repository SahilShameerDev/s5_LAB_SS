#include <stdio.h>

// Structure to represent a process
struct process {
    int pid;               // Process ID
    int burst_time;        // Burst time of the process
    int priority;          // Priority of the process
    int waiting_time;      // Waiting time of the process
    int turn_around_time;  // Turn around time of the process
};

// Function to add a process
void addprocess(struct process proc[], int bt, int p, int i) {
    proc[i].burst_time = bt;
    proc[i].priority = p;
    proc[i].pid = i + 1; // Assign a process ID starting from 1
}

// Function to sort the processes based on priority
void sort(struct process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                // Swap burst time
                int temp = proc[i].burst_time;
                proc[i].burst_time = proc[j].burst_time;
                proc[j].burst_time = temp;
                // Swap priority
                temp = proc[i].priority;
                proc[i].priority = proc[j].priority;
                proc[j].priority = temp;
                // Swap process ID
                temp = proc[i].pid;
                proc[i].pid = proc[j].pid;
                proc[j].pid = temp;
            }
        }
    }
}

// Function to calculate the waiting time and turn around time for each process
void calc(struct process proc[], int n) {
    proc[0].waiting_time = 0; // First process has a waiting time of 0
    proc[0].turn_around_time = proc[0].burst_time; // Turn around time is the burst time for the first process

    for (int i = 1; i < n; i++) {
        // Waiting time is the sum of the waiting time and burst time of the previous process
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
        // Turn around time is the sum of the waiting time and burst time of the current process
        proc[i].turn_around_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

// Function to display the Gantt chart
void gantt_chart(struct process proc[], int n) {
    printf("\nGantt Chart\n");
    printf("PID\tPriority\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].priority, proc[i].burst_time, proc[i].waiting_time, proc[i].turn_around_time);
    }
}

// Function to calculate and display the average waiting time and turn around time
void avg(struct process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turn_around_time;
    }
    printf("Average Waiting Time: %f\n", (float)total_wt / n);
    printf("Average Turn Around Time: %f\n", (float)total_tat / n);
}

int main() {
    int n; // Variable to store the number of processes

    // Ask the user to enter the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array to store the processes
    struct process proc[n];

    // Loop to get the burst time and priority for each process from the user
    for (int i = 0; i < n; i++) {
        int bt, pt; // Variables to store burst time and priority
        printf("Enter the burst time and priority for process %d: ", i + 1);
        scanf("%d%d", &bt, &pt);
        addprocess(proc, bt, pt, i);
    }

    // Sort processes by priority
    sort(proc, n);

    // Calculate waiting time and turn around time for each process
    calc(proc, n);

    // Display the Gantt chart
    gantt_chart(proc, n);

    // Calculate and display the average waiting time and turn around time
    avg(proc, n);

    return 0; // Indicate that the program ended successfully
}

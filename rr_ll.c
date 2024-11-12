#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turn_around_time;
    int start_time;
    int end_time;
    struct process *next;
};
struct process *head = NULL;
struct process *current = NULL;

void add_process(int bt, int i) {
    struct process *np = (struct process*)malloc(sizeof(struct process));
    np->burst_time = bt;
    np->remaining_time = bt;
    np->pid = i;
    np->waiting_time = 0;
    np->turn_around_time = 0;
    np->start_time = 0;
    np->end_time = 0;
    np->next = NULL;

    if (head == NULL) {
        head = np;
        current = head;
    } else {
        current->next = np;
        current = np;
    }
}

void round_robin(int tq){
    struct process *t ;
    int done;
    int time = 0;

    do{
        t=head;
        
        done = 1;
        while(t){
            if(t->remaining_time > 0){
                done = 0;
                if(t->remaining_time > tq){
                    t->start_time = time;
                    time += tq;
                    t->remaining_time -= tq;
                    t->end_time = time;
                    
                }else{
                    t->start_time = time;
                    time += t->remaining_time;
                    t->waiting_time = time - t->burst_time;
                    t->turn_around_time = time;
                    t->end_time = time;
                    t->remaining_time = 0;
                }
                printf("\nPID: %d, Start time: %d, End Time: %d\n" ,t->pid, t->start_time, t->end_time);
            }
            t = t->next;
        }
    }while(!done);
}

void gantt_chart(int n) {
    struct process *t = head;
    printf("\nGantt Chart\n");
    printf("PID\tBurst Time\tStart Time\tEnd Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", t->pid, t->burst_time, t->start_time, t->end_time);
        t = t->next;
    }
}

void avg(int n) {
    struct process *t = head;
    int wt = 0, tat = 0;

    for (int i = 0; i < n; i++) {
        wt += t->waiting_time;
        tat += t->turn_around_time;
        t = t->next;
    }

    printf("Average Waiting Time: %.2f\n", (float)wt / n);
    printf("Average Turn Around Time: %.2f\n", (float)tat / n);
}

int main() {
    int n, bt, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &bt);
        add_process(bt, i + 1);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    round_robin(time_quantum);

    gantt_chart(n);

    avg(n);

    return 0;
}

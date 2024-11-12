// SJF Cpu Scheduling using linked list

#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    struct process *next;
};
struct process *head = NULL;
struct process *current = NULL;

void addprocess(int bt, int i){
    struct process *np = (struct process*)malloc(sizeof(struct process));
    np->burst_time = bt;
    np->pid = i;
    np->next = NULL;

    if (head == NULL)
    {
        head = np;
        current = head;
    }
    else
    {
        current->next = np;
        current = np;
    }
}

void sort(){
    struct process *t = head;
    struct process *c,*min;
    int m;
    

    while(t){
        c=t->next;
        min = t;

        while(c){
            if(c->burst_time<min->burst_time){
                min = c;
            }
            c= c->next;
        }
        m = t->burst_time;
        t->burst_time = min->burst_time;
        t->pid = min->pid;
        t->waiting_time = min->waiting_time;
        t->turn_around_time = min->turn_around_time;
        min->burst_time = m;
        t=t->next;
    }
}
void calc(int n){
    struct process *t = head;
    int wt = 0;

    for(int i=0;i<n;i++){
        t->waiting_time = wt;
        t->turn_around_time = wt + t->burst_time;
        wt = wt + t->burst_time;
        t= t->next;
    }

}

void gantt_chart(int n){
    struct process *t = head;
    printf("\nGantt Chart\n");
    printf("PID\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t\t%d\t\t%d\n", t->pid, t->burst_time, t->waiting_time, t->turn_around_time);
        t=t->next;
    }

}

void avg(int n){
    struct process *t = head;
    int wt = 0, tat = 0;

    for(int i=0;i<n;i++){
        wt = wt + t->waiting_time;
        tat = tat + t->turn_around_time;
        t = t->next;
    }

    printf("Average Waiting Time: %f\n", (float)wt/n);
    printf("Average Turn Around Time: %f\n", (float)tat/n);

}

void main(){
    int n,bt;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i=0;i<n;i++){
        printf("Enter the burst time for process %d: ", i+1);
        scanf("%d", &bt);
        addprocess(bt, i+1);
    }

    sort();

    calc(n);

    gantt_chart(n);

    avg(n);
}
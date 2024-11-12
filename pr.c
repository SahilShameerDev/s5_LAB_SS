#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turn_around_time;
};

struct process pr[20];

void sort(int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(pr[i].priority>pr[j].priority){
                struct process temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;
            }
        }
    }
}

void calc(int n){
    pr[0].waiting_time = 0;
    pr[0].turn_around_time = pr[0].burst_time ;
    for(int i = 1; i<n; i++){
        pr[i].waiting_time = pr[i-1].waiting_time + pr[i-1].burst_time;
        pr[i].turn_around_time = pr[i].waiting_time+pr[i].burst_time;
    }
}

void gantt_chart(int n){
    printf("\nGantt Chart\n");
    printf("PID\tBurst Time\tPriority\tWaiting Time\tTurn Around Time\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", pr[i].pid, pr[i].burst_time, pr[i].priority, pr[i].waiting_time, pr[i].turn_around_time);
    }
}

void avg(int n){
    int wt = 0, tat = 0;
    for(int i=0;i<n;i++){
        wt += pr[i].waiting_time;
        tat += pr[i].turn_around_time;
    }
    printf("Average waiting time: %f\n", (float)wt/n);
    printf("Average turn around time: %f\n", (float)tat/n);
}

void main(){
    int n;

    printf("enter number of proccess:");
    scanf("%d", &n);
    

    for(int i=0;i<n;i++){
        printf("Enter the burst time and priority for process %d: ", i+1);
        scanf("%d%d", &pr[i].burst_time, &pr[i].priority);
        pr[i].pid = i+1;
    }

    sort(n);

    calc(n);

    gantt_chart(n);

    avg(n);
}
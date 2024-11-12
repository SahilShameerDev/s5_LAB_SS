#include <stdio.h>
int main()
{
    int n, at[10], bt[10], wt[10], tat[10], ct[10], pr[10], sum, i, j, k, pos, temp;
    float totaltat = 0, totalwt = 0;
    printf("Enter the total number of processes:");
    scanf("%d", &n);
    printf("\nEnter The Process Burst Time\n");
    for (i = 0; i < n; i++)
    {
        printf("Enter Burst time of process[%d]:", i + 1);
        scanf("%d", &bt[i]);
    }
    printf("\nEnter The Priority of each process \n");
    for (i = 0; i < n; i++)
    {
        printf("Enter priority of process[%d]:", i + 1);
        scanf("%d", &pr[i]);
    }
    /* Apply Selection sort to sort according to burst time and process priority */
    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (pr[j] < pr[pos])
            {
                pos = j;
            }
        }
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
    }
    /* Calculate completion time of processes */ //commenting issue
        sum = 0;
    for (j = 0; j < n; j++)
    {
        sum = sum + bt[j];
        ct[j] = sum;
        printf("%d\t", ct[j]);
    }
    /*Calculate Turn Around time */
    for (k = 0; k < n; k++)
    {
        tat[k] = ct[k];
        totaltat = totaltat + tat[k];
    }
    /* Calculate Waiting time */
    for (k = 0; k < n; k++)
    {
        wt[k] = tat[k] - bt[k];
        totalwt = totalwt + wt[k];
    }
    printf("\nProcess\tBT\tTAT\tWT\n\n\n");
    for (i = 0; i < n; i++)
    {
        printf("\nP%d\t %d\t %d\t %d\n\n", i + 1, bt[i], tat[i], wt[i]);
    }
    printf("\nAverage TurnaroundTime:%f\n", totaltat / n);
    printf("\nAverage Waiting Time:%f", totalwt / n);
    return 0; //ividem entho issue undayo backspace adich pinnem ezuthiyappa thanne sheri aayi
}
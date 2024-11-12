#include <stdio.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
int main()
{
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {0};
    int max[MAX_PROCESSES][MAX_RESOURCES] = {0};
    int need[MAX_PROCESSES][MAX_RESOURCES] = {0};
    int available[MAX_RESOURCES] = {0};
    int work[MAX_RESOURCES] = {0};
    int finish[MAX_PROCESSES] = {0};
    int safety = 0;
    int safe_sequence[MAX_PROCESSES] = {0};
    int i, j, k, count = 0;

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < MAX_PROCESSES; i++)
        for (j = 0; j < MAX_RESOURCES; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter the max matrix:\n");
    for (i = 0; i < MAX_PROCESSES; i++)
        for (j = 0; j < MAX_RESOURCES; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the available resources:\n");
    for (i = 0; i < MAX_RESOURCES; i++)
        scanf("%d", &available[i]);

    for (i = 0; i < MAX_PROCESSES; i++)
        for (j = 0; j < MAX_RESOURCES; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    printf("Need matrix is: \n");
    for (i = 0; i < MAX_PROCESSES; i++)
    {
        printf("P%d: ", i + 1);
        for (j = 0; j < MAX_RESOURCES; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }


    while (count < MAX_PROCESSES)
    {
        for (i = 0; i < MAX_PROCESSES; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 1;
                for (j = 0; j < MAX_RESOURCES; j++){
                    if (need[i][j] > work[j])       // need[i][j] > work[j] means that the process cannot be allocated the resources
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag) // if flag is 1, then the process can be allocated the resources
                    break;
            }
        }
        if (i == MAX_PROCESSES)
        {
            printf("System is in an unsafe state.\n");
            return -1;
        }
        count++;
        safe_sequence[count - 1] = i;
        for (j = 0; j < MAX_RESOURCES; j++)
            work[j] += allocation[i][j];
        finish[i] = 1;
    }
    if (count == MAX_PROCESSES)
    {
        printf("System is in a safe state.\n");
        printf("Safe sequence is: ");
        for (i = 0; i < MAX_PROCESSES; i++)
            printf(" P%d", safe_sequence[i] + 1);
        printf("\n");
    return 0;
}

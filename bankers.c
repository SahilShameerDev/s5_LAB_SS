#include <stdio.h>

#define maxR 3
#define maxP 4

void main()
{
    int allocation[maxP][maxR] = {0};
    int max[maxP][maxR] = {0};
    int need[maxP][maxR] = {0};
    int available[maxR] = {0};
    int finish[maxP] = {0};
    int work[maxR] = {0};
    int safeseq[maxP] = {0};
    int safety = 0;
    int i, j, k, count = 0;

    printf("Enter allocation matrix:");
    for (i = 0; i < maxP; i++)
    {
        for (j = 0; j < maxR; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
        printf("\n");
    }

    printf("Enter max matrix:");
    for (i = 0; i < maxP; i++)
    {
        for (j = 0; j < maxR; j++)
        {
            scanf("%d", &max[i][j]);
        }
        printf("\n");
    }

    printf("Enter available:");
    for (i = 0; i < maxR; i++)
    {
        scanf("%d", &available[i]);
    }

    for (i = 0; i < maxP; i++)
    {
        for (j = 0; j < maxR; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    printf(" Need matrix:");
    for (i = 0; i < maxP; i++)
    {
        printf("P%d: ", i + 1);
        for (j = 0; j < maxR; j++)
        {
            printf("%d", max[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < maxR; i++)
    {
        work[i] = available[i];
    }

    while (count < maxP)
    {
        for (i = 0; i < maxP; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 1;
                for (j = 0; j < maxR; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                {
                    break;
                }
            }
        }
        if (i == maxP)
        {
            printf("System is unsafe");
            return;
        }
        count++;
        safeseq[count - 1] = i;
        for (j = 0; j < maxR; j++)
        {
            work[j] += allocation[i][j];
        }
        finish[i] = 1;
    }

    if (count == maxP)
    {
        printf("System is in safe state");
        printf("Safe sequence is:\n");
        for (i = 0; i < maxP; i++)
        {
            printf("P%d,", safeseq[i]);
        }
        printf("\n");
    }
}
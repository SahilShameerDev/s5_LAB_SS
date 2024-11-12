#include <stdio.h>
int main()
{
    int i, j, k, f, pf = 0, count = 0, rf[25], m[10], n;
    // get required inputs
    printf("\nEnter the length: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &rf[i]);
    printf("\nEnter no. of frames: ");
    scanf("%d", &f);
    //Set all frames as empty
    for (i = 0; i < f; i++)
        m[i] = -1;
    // Page Replacement Process
    printf("The Page Replacement Process : \n");
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < f; k++)
        {
            if (m[k] == rf[i])
                break;
        }
        if (k == f)
        {
            m[count++] = rf[i];
            pf++;
        }
        for (j = 0; j < f; j++)
            printf(" \t%2d", m[j]);
        if (k == f)
            printf("\tPage Fault\n");
        else
            printf("\tPage Hit\n");
        if (count == f)
            count = 0;
    }
    printf("\n The number of Page Faults: %d\n", pf);
}
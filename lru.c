#include <stdio.h>
// Declare global variables:
// i,j,k - Loop counters
// min - Index of frame with minimum count (least recently used)
// rs[25] - Array to store reference string
// m[10] - Array to store frames
// count[10] - Array to track when each frame was last used
// flag[25] - Array to mark page hits/faults
// n - Length of reference string
// f - Number of frames
// pf - Page fault counter
// next - Counter for tracking frame usage order
int i, j, k, min, rs[25], m[10], count[10], flag[25], n, f, pf = 0, next = 1;

int main()
{
    // Get length of reference string
    printf("\n Enter the length: ");
    scanf("%d", &n);

    // Input the reference string and initialize flags to 0
    printf(" Enter the reference string : ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &rs[i]);
        flag[i] = 0;
    }

    // Get number of frames
    printf(" Enter the number of frames: ");
    scanf("%d", &f);

    // Initialize frames to -1 and their counts to 0
    for (i = 0; i < f; i++)
    {
        count[i] = 0;
        m[i] = -1;
    }

    printf("\n The Page Replacement process : \n");

    // Process each page in reference string
    for (i = 0; i < n; i++)
    {
        // Check if page already exists in any frame
        for (j = 0; j < f; j++)
        {
            if (m[j] == rs[i])
            {
                flag[i] = 1;  // Mark as page hit
                count[j] = next;  // Update last used time
                next++;
            }
        }

        // If page fault occurs (page not found)
        if (flag[i] == 0)
        {
            // If frames are still empty, place page in next empty frame
            if (i < f)
            {
                m[i] = rs[i];
                count[i] = next;
                next++;
            }
            // If all frames full, replace least recently used page
            else
            {
                min = 0;
                // Find frame with minimum count (least recently used)
                for (j = 1; j < f; j++)
                    if (count[min] > count[j])
                        min = j;
                m[min] = rs[i];  // Replace page
                count[min] = next;  // Update usage time
                next++;
            }
            pf++;  // Increment page fault counter
        }

        // Print current state of frames
        for (j = 0; j < f; j++)
            printf("%d\t", m[j]);

        // Print whether page fault or hit occurred
        if (flag[i] == 0)
            printf("Page Fault No. %d\n", pf);
        else
            printf("Page Hit No. %d", pf);
        printf("\n");
    }

    // Print total number of page faults
    printf("\n The number of page faults  %d", pf);
}
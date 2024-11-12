#include <stdio.h>
// Declare global variables:
// i,j,k - Loop counters
// f - Number of frames
// pf - Page fault counter initialized to 0
// count - Counter initialized to 0
// flag - Used to track if page is found in frames
// rs[25] - Array to store reference string
// m[10] - Array to store frames
// freq[10] - Array to track frequency of each page
// n - Length of reference string
int i, j, k, f, pf = 0, count = 0, flag, rs[25], m[10], freq[10], n;

void main()
{
    // Get length of reference string from user
    printf("\nEnter the length: ");
    scanf("%d", &n);

    // Input the reference string
    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &rs[i]);

    // Get number of frames
    printf("Enter no. of frames: ");
    scanf("%d", &f);

    // Initialize all frames to -1 (empty) and their frequencies to 0
    for (i = 0; i < f; i++)
    {
        m[i] = -1;
        freq[i] = 0; 
    }

    // Print header for the page replacement process
    printf("The Page Replacement Process : \n");
    printf("Page No\t\t\tFrames\t\t\tStatus");

    // Process each page in reference string
    for (i = 0; i < n; i++)
    {
        flag = 0;  // Reset page found flag
        printf("\n%d\t\t", rs[i]);  // Print current page number

        // Check if page already exists in any frame
        for (k = 0; k < f; k++)
        {
            if (m[k] == rs[i])
            {
                flag = 1;  // Mark page as found
                freq[k]++;  // Increment frequency of this page
                // Print current state of frames
                for (j = 0; j < f; j++)
                    printf("%2d\t", m[j]);
                printf("\tPage Hit\n");  // Indicate page hit
                break;
            }
        }

        // If page fault occurs (page not found)
        if (flag == 0)
        {
            // Find frame with minimum frequency for replacement
            int min_freq = freq[0];
            int min_freq_index = 0;
            for (j = 1; j < f; j++)
            {
                if (freq[j] < min_freq)
                {
                    min_freq = freq[j];
                    min_freq_index = j;
                }
            }
            // Replace page in frame with minimum frequency
            m[min_freq_index] = rs[i];
            freq[min_freq_index] = 1;  // Set frequency of new page to 1
            pf++;  // Increment page fault counter

            // Print current state of frames
            for (j = 0; j < f; j++)
                printf("%2d\t", m[j]);
            if (k == f)
                printf("\tPage Fault\n");
        }
    }

    // Print final statistics
    printf("\n\nNo of page faults : %d\nNo of page hits : %d\n", pf, n - pf);
}
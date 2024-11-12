#include<stdio.h>
#include<stdlib.h>

struct memo {
    int blkno;
    int size;
    int total;
    struct memo *link;
};

struct memo *header;
struct memo *ptr;
struct memo *loc;

void create(int B[], int N) {
    int i, item = 1;
    header = NULL;
    for (i = 0; i < N; i++) {
        struct memo *temp = (struct memo *)malloc(sizeof(struct memo));
        if (temp == NULL) {
            printf("cannot create\n");
            break;
        } else {
            if (header == NULL) {
                header = temp;
            } else {
                ptr = header;
                while (ptr->link != NULL) {
                    ptr = ptr->link;
                }
                ptr->link = temp;
            }
            temp->link = NULL;
            temp->blkno = i + 1;
            temp->size = B[i];
            temp->total = B[i];
        }
    }
}

void display() {
    int i;
    printf("\nFree Block\tTotal Size\tSize left");
    ptr = header;
    while (ptr != NULL) {
        printf("\n%d\t\t%d\t\t%d", ptr->blkno, ptr->total, ptr->size);
        ptr = ptr->link;
    }
}

void firstfit(int a[], int b[], int n, int s) {
    create(b, s);
    int flag, z;
    for (int i = 0; i < n; i++) {
        flag = 0;
        ptr = header;
        while (ptr != NULL) {
            if (a[i] <= ptr->size) {
                flag = 1;
                break;
            }
            ptr = ptr->link;
        }
        if (flag == 1) {
            ptr->size -= a[i];
        } else {
            printf("there are waiting processes\n");
        }
    }
    display();
}

void bestfit(int a[], int b[], int n, int s) {
    create(b, s);
    int x, y, z;
    for (int i = 0; i < n; i++) {
        loc = NULL;
        ptr = header;
        while (ptr != NULL) {
            x = ptr->size;
            if (a[i] == x) {
                loc = ptr;
                break;
            }
            ptr = ptr->link;
        }
        while (ptr != NULL && loc == NULL) {
            x = ptr->size;
            y = loc->size;
            if (a[i] <= x && x <= y) {
                loc = ptr;
            }
            ptr = ptr->link;
        }
        if (loc != NULL) {
            loc->size -= a[i];
        }
    }
    display();
}

void worstfit(int a[], int b[], int n, int s) {
    create(b, s);
    for (int i = 0; i < n; i++) {
        loc = NULL;
        ptr = header;
        while (ptr != NULL) {
            if (a[i] <= ptr->size && (loc == NULL || ptr->size > loc->size)) {
                loc = ptr;
            }
            ptr = ptr->link;
        }
        if (loc != NULL) {
            loc->size -= a[i];
        }
    }
    display();
}

void main(){
    int op, i, n, s;
    int pr[10], sb[10];

    printf("Enter number of blocks\t");
    scanf("%d", &s);
    printf("Enter size of each block\t");
    for (i = 0; i < s; i++) {
        scanf("%d", &sb[i]);
    }
    printf("Enter number of processes\t");
    scanf("%d", &n);
    printf("Enter the size of each process:\t");
    for (i = 0; i < n; i++) {
        scanf("%d", &pr[i]);
    }

    printf("\n1.First fit\n2.Best fit\n3.Worst fit\n4.Exit\n");

    do {
        printf("\nEnter option:\t");
        scanf("%d", &op);
        switch (op) {
            case 1:
                firstfit(pr, sb, n, s);
                break;
            case 2:
                bestfit(pr, sb, n, s);
                break;
            case 3:
                worstfit(pr, sb, n, s);
                break;
            case 4:
                break;
            default:
                printf("Invalid option\n");
        }
    } while (op != 4);
}
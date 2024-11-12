#include<stdio.h>
#include<string.h>

int main() {
    char input[10];
    int start, length, address;
    FILE *fp1, *fp2;
    
    fp1 = fopen("input2.dat", "r");
    fp2 = fopen("out2.dat", "w");
    
    fscanf(fp1, "%s", input);
    
    while(strcmp(input, "E") != 0) {
        if(strcmp(input, "H") == 0) {
            fscanf(fp1, "%d", &start);
            fscanf(fp1, "%d", &length);
            fscanf(fp1, "%s", input);
        } else if(strcmp(input, "T") == 0) {
            fscanf(fp1, "%d", &address);
            fscanf(fp1, "%s", input);
            fprintf(fp2, "%d\t%c%c\n", address, input[0], input[1]);
            fprintf(fp2, "%d\t%c%c\n", address + 1, input[2], input[3]);
            fprintf(fp2, "%d\t%c%c\n", address + 2, input[4], input[5]);
            address += 3;
            fscanf(fp1, "%s", input);
        } else {
            fprintf(fp2, "%d\t%c%c\n", address, input[0], input[1]);
            fprintf(fp2, "%d\t%c%c\n", address + 1, input[2], input[3]);
            fprintf(fp2, "%d\t%c%c\n", address + 2, input[4], input[5]);
            address += 3;
            fscanf(fp1, "%s", input);
        }
    }
    fclose(fp1);
    fclose(fp2);
    
    printf("finished");
    return 0;
}

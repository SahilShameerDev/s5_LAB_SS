#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    char add[6], length[10], input[10], binary[12], bitmask[12], relocbit;
    int start, inp, len, i, address, opcode, addr, actualadd;
    FILE *fp1, *fp2;
    
    printf("Enter the actual starting address: ");
    scanf("%d", &start);
    
    fp1 = fopen("relinput.dat", "r");
    fp2 = fopen("reloutput.dat", "w");
    
    fscanf(fp1, "%s", input);
    
    while(strcmp(input, "E") != 0) {
        if(strcmp(input, "H") == 0) {
            fscanf(fp1, "%s", add);
            fscanf(fp1, "%s", length);
            fscanf(fp1, "%s", input);
        }
        
        if(strcmp(input, "T") == 0) {
            fscanf(fp1, "%d", &address);
            fscanf(fp1, "%s", bitmask);
            address += start - 1000;
            len = strlen(bitmask);
            
            for(i = 0; i < len; i++) {
                fscanf(fp1, "%d", &opcode);
                fscanf(fp1, "%d", &addr);
                relocbit = bitmask[i];
                
                if(relocbit == '0')
                    actualadd = addr;
                else
                    actualadd = addr + start;
                
                fprintf(fp2, "%d\t%d%d\n", address, opcode, actualadd);
                address += 3;
            }
            fscanf(fp1, "%s", input);
        }
    }
    fclose(fp1);
    fclose(fp2);
    
    return 0;
}

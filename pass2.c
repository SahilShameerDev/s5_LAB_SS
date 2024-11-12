// Include necessary header files for input/output, string manipulation, and standard library functions
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
    // Declare arrays to store various components of assembly code and object code
    char a[10],ad[10],label[10],opcode[10],operand[10],mnemonic[10],symbol[10],start[10],t[200],t1[200],c1[10],a1[10];
    // Declare integer variables for addresses, codes, lengths etc.
    int i,address,code,add,len,actual_len,tlen=0;
    // Declare file pointers for various input/output files
    FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
    
    // Initialize empty strings
    strcpy(t1,"");

    // Open required files:
    fp1=fopen("assmlist.dat","w"); // For writing assembly listing
    fp2=fopen("symtab.dat","r");   // For reading symbol table
    fp3=fopen("intermediate.dat","r"); // For reading intermediate code
    fp4=fopen("optab.dat","r");    // For reading operation codes
    fp5=fopen("objrcd.dat","w");   // For writing object code
    fp6=fopen("len.dat","r");      // For reading program length

    // Read first line from intermediate file
    fscanf(fp3,"%s%s%s",label,opcode,operand);

    // Handle START directive if present
    if(strcmp(opcode,"START")==0)
    {
        fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);
        strcpy(start,operand);      // Save start address
        fscanf(fp6,"%d",&len);     // Read program length
        // Write header record to object file
        fprintf(fp5,"H^%-6s^00%s^0000%d\nT^00%s^",label,operand,len,operand);
        fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
        fclose(fp6);
    }

    // Process each instruction until END is encountered
    while(strcmp(opcode,"END")!=0)
    {
        // Handle BYTE directive
        if(strcmp(opcode,"BYTE")==0)
        {
            fprintf(fp1,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
            len=strlen(operand);
            actual_len=len-3;
            // Convert each character to hex
            for(i=2;i<(actual_len+2);i++)
            {
                sprintf(ad,"%d",operand[i]);
                fprintf(fp1,"%s",ad);
                // Check if text record length would exceed 60
                if((tlen+2*actual_len)<=60)
                {
                    strcat(t1,ad);
                }
                else
                {
                    // Write current text record and start new one
                    fprintf(fp5,"%d^%s",tlen/2,t1);
                    fprintf(fp5,"\nT^00%d",address);
                    tlen=0;
                    strcpy(t1,"");
                    strcat(t1,ad);
                }
            }
            fprintf(fp1,"\n");
            strcat(t1,"^");
            tlen+=2*actual_len;
        }

        // Handle WORD directive
        else if(strcmp(opcode,"WORD")==0)
        {
            // Get length of operand and store operand value in string a
            len=strlen(operand);
            sprintf(a,"%s",operand);

            // Write to listing file: address, label, opcode, operand, and object code
            // Object code format: 00000 followed by operand value
            fprintf(fp1,"%d\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,a);

            // Check if adding 6 bytes (object code length) would exceed text record limit of 60
            if((tlen+6)<=60)
            {
                // Add object code to current text record
                strcat(t1,"00000"); // Add leading zeros
                strcat(t1,a);       // Add operand value
                strcat(t1,"^");     // Add delimiter
            }
            else
            {
                // Write current text record and start new one
                fprintf(fp5,"%d^%s",tlen/2,t1);        // Write length and content
                fprintf(fp5,"\nT^00%d",address);       // Start new record with address
                tlen=0;                                // Reset length counter
                strcpy(t1,"");                         // Clear text record buffer
                strcat(t1,"0000");                     // Add leading zeros
                strcat(t1,a);                          // Add operand value
                strcat(t1,"^");                        // Add delimiter
            }
            tlen+=6;  // Increment text record length by 6 bytes
        }

        // Handle RESB and RESW directives
        else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0))
        {
            fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
        }

        // Handle machine instructions
        else
        {
            rewind(fp4); // Reset opcode table file pointer
            fscanf(fp4,"%s%d",mnemonic,&code);
            // Find matching opcode
            while(strcmp(opcode,mnemonic)!=0)
                fscanf(fp4,"%s%d",mnemonic,&code);

            // Handle instructions with no operand
            if(strcmp(operand,"**")==0)
            {
                fprintf(fp1,"%d\t%s\t%s\t%s\t%d0000\n",address,label,opcode,operand,code);
            }
            // Handle instructions with operand
            else
            {
                rewind(fp2); // Reset symbol table file pointer
                fscanf(fp2,"%s%d",symbol,&add);
                // Find matching symbol
                while(strcmp(operand,symbol)!=0)
                {
                    fscanf(fp2,"%s%d",symbol,&add);
                }
                fprintf(fp1,"%d\t%s\t%s\t%s\t%d%d\n",address,label,opcode,operand,code,add);
                sprintf(c1,"%d",code);
                sprintf(a1,"%d",add);

                if((tlen+6)<=60)
                {
                    strcat(t1,c1);
                    strcat(t1,a1);
                    strcat(t1,"^");
                }
                else
                {
                    // Write current text record and start new one
                    fprintf(fp5,"%d^%s",tlen/2,t1);
                    fprintf(fp5,"\nT^00%d",address);
                    tlen=0;
                    fprintf(fp5,"%s",t1);
                    strcpy(t1,"");
                    strcat(t1,a1);
                    strcat(t1,"^");
                }
                tlen+=6;
            }
        }
        // Read next instruction
        fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
    }

    // Write final text record
    fprintf(fp5,"%d^%s",tlen/2,t1);
    fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
    // Write end record
    fprintf(fp5,"\nE^00%s",start);
    printf("\nFinished\n");

    // Close all files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}

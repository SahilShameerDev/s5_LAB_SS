#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Main function
void main() {
    // Variables for storing different code components
    char label[10], opcode[10], operand[10], mnemonic[10];
    char start[10], text_record[200] = "", object_code[10];
    int address, code, length, record_length = 0;

    // Open necessary files
    FILE *assm_list = fopen("assmlist.dat", "w");    // For writing the assembly listing
    FILE *symtab = fopen("symtab.dat", "r");         // For reading the symbol table
    FILE *intermediate = fopen("intermediate.dat", "r"); // For reading the intermediate code
    FILE *optab = fopen("optab.dat", "r");           // For reading operation codes
    FILE *obj_code = fopen("objrcd.dat", "w");       // For writing the final object code
    FILE *len_file = fopen("len.dat", "r");          // For reading the program length

    // Read first line from intermediate file (could contain START directive)
    fscanf(intermediate, "%s%s%s", label, opcode, operand);

    // If a START directive is found, initialize header for object code
    if (strcmp(opcode, "START") == 0) {
        fprintf(assm_list, "\t%s\t%s\t%s\n", label, opcode, operand); // Write to assembly listing
        strcpy(start, operand);                                      // Store starting address
        fscanf(len_file, "%d", &length);                             // Read program length
        // Write header record in object code file
        fprintf(obj_code, "H^%-6s^00%s^0000%d\nT^00%s^", label, operand, length, operand);
        // Move to the next line in intermediate file
        fscanf(intermediate, "%d%s%s%s", &address, label, opcode, operand);
        fclose(len_file);   // Close length file after reading program length
    }

    // Process each line until "END" directive is encountered
    while (strcmp(opcode, "END") != 0) {
        // Write current line address, label, opcode, and operand to assembly listing
        fprintf(assm_list, "%d\t%s\t%s\t%s\t", address, label, opcode, operand);

        // Handle BYTE directive (usually for storing characters as hexadecimal)
        if (strcmp(opcode, "BYTE") == 0) {
            int byte_length = strlen(operand) - 3; // Length of characters between quotes
            for (int i = 2; i < byte_length + 2; i++) {  // Skip starting characters like C' '
                sprintf(object_code, "%02X", operand[i]); // Convert each character to hex
                strcat(text_record, object_code);         // Append to current text record
            }
            record_length += byte_length * 2; // Update record length (hex code length)
        }
        // Handle WORD directive (usually for storing integer values)
        else if (strcmp(opcode, "WORD") == 0) {
            sprintf(object_code, "%06X", atoi(operand)); // Convert operand to hex, padded to 6 chars
            strcat(text_record, object_code);            // Append to text record
            record_length += 6;                          // Update record length (WORD is 3 bytes)
        }
        // Handle RESB and RESW directives (reserved memory, no object code generated)
        else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0) {
            // Skip object code generation; only write listing
        }
        // Handle machine instructions
        else {
            rewind(optab);   // Reset optab file pointer to start
            // Find matching opcode in optab
            while (fscanf(optab, "%s%d", mnemonic, &code) && strcmp(opcode, mnemonic) != 0);

            // If no operand is specified (like RSUB), use zero address
            if (strcmp(operand, "**") == 0) {
                sprintf(object_code, "%02X0000", code); // Code + 0000 as address
            } else {
                // Search symbol table for operand address
                rewind(symtab);  // Reset symtab file pointer to start
                int symbol_address;
                // Find operand in symbol table
                while (fscanf(symtab, "%s%d", mnemonic, &symbol_address) && strcmp(operand, mnemonic) != 0);
                sprintf(object_code, "%02X%04X", code, symbol_address); // Code + symbol address
            }
            strcat(text_record, object_code); // Append generated code to text record
            record_length += 6;               // Machine instructions are typically 3 bytes
        }

        // Check if text record length exceeds 30 bytes (60 hex characters)
        if (record_length >= 30) {
            // Write current text record to object file
            fprintf(obj_code, "%02X^%s\nT^00%d^", record_length / 2, text_record, address);
            record_length = 0;                  // Reset record length for new record
            strcpy(text_record, "");            // Clear text record buffer
        }

        // Write object code of current line to assembly listing file
        fprintf(assm_list, "%s\n", object_code);
        // Read next line in intermediate file
        fscanf(intermediate, "%d%s%s%s", &address, label, opcode, operand);
    }

    // Write the last text record (if any remaining)
    if (record_length > 0)
        fprintf(obj_code, "%02X^%s", record_length / 2, text_record);

    // Write end record to object file to indicate program end
    fprintf(obj_code, "\nE^00%s", start);

    // Close all open files
    fclose(assm_list);
    fclose(symtab);
    fclose(intermediate);
    fclose(optab);
    fclose(obj_code);

    // Indicate completion
    printf("Finished\n");
}

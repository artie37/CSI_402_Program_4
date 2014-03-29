// utilites.c
// Arthur Knapp
// AK146316

// Function Descriptions:

// loadOpcodes:
// This function loads opcodes into the opcodeTable struct array. This will be done by opening and reading
// the opcodes file line by line while there are values left to be read. Each time a value is read, it will
// be stored in the opcodeTable struct.

// openFiles:
// This function opens all of the files used in this program. There is an assembly file, symbol table file,
// object file, and error file. All of these files have the same name but their file extensions need to be
// added to the file name. First, the assembly file is opened. Then, the function checks the assembly file
// name to see if it has a file extension. If it does, the file extension is removed. If it doesn't, nothing
// is done. After the file extension is removed, the name is copied into three new character arrays and new
// file extensions are added to them. After the extensions are added to the names, the three files are opened.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

void loadOpcodes()
{
    FILE *opcodeFile;
    // File pointer to store the opcode text file
    int i = 0;
    // Int variable to loop through the opcode table struct array
    OpCodeTable opcodeTable[OPTABLE_SIZE];
    // Struct array definition
    
    if openOpcodeFile(opcodeFile)
    // Open opcodes file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Couldn't Open Opcodes File\n");
        exit(1);
    }
    
    for opTableCondition(i)
    // Loop through the opcode file
    {
        fscanf(opcodeFile, "%d %s %c", &opcodeTable[i].opcode,
               opcodeTable[i].mnemonic, &opcodeTable[i].format);
        // Reads the opcode, mnemonic, and the format from the opcode file and
        // store it in the opcode table.
    }
    
// Print opcode table for testing purposes
//    i = 0;
//    
//    for opTableCondition(i)
//    {
//        printf("%d %s %c\n", opcodeTable[i].opcode, opcodeTable[i].mnemonic, opcodeTable[i].format);
//    }
//    
    if closeOpcodeFile(opcodeFile)
    // Close opcodes file. If it doesn't close, print error message and close program.
    {
        fprintf(stderr, "Error: Couldn't Close Opcodes File\n");
        exit(i);
    }
}

void openFiles(char *asmName)
{
    char symName[(int)strlen(asmName) + 4];
    char objName[(int)strlen(asmName) + 4];
    char errName[(int)strlen(asmName) + 4];
    // Define character arrays 4 larger than inFile to store ".sym", ".obj", ".err"
    
    int i = (int)strlen(asmName);
    // Int variable to store the string length of asmFile and loop through it
    int j = i;
    // Int variable to compare to i
    
    if openAsmFile(asmFile, asmName)
    // Open assembly file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Couldn't Open Assembly File\n");
        exit(1);
    }
    
    for findPeriod(asmName, i);
    // Loop through character array until the first '.'
    
    if noExt(i, BEGINING_OF_STRING)
    // Checks if there is no file extension. If there isn't, do nothing.
    {}
    
    else
    // If there is a file extension, delete extension
    {
        for delExt(i, j)
        // For loop to delete extension
        {
            asmName[i] = '\0';
        }
    }
    
    strcpy(symName, asmName);
    strcpy(objName, asmName);
    strcpy(errName, asmName);
    // Copy the name of the input file into symFile, objFile, and errFile
    
    strcat(symName, ".sym");
    strcat(objName, ".obj");
    strcat(errName, ".err");
    // Append the extension to the end of the file name
 
//    print file names for testing purposes
//    printf("%s\n", symName);
//    printf("%s\n", objName);
//    printf("%s\n", errName);
    
    if openSymFile(symFile, symName)
    // Open symbol table file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Symbol Table File Did Not Open\n");
        exit(1);
    }
    
    if openObjFile(objFile, objName)
    // Open object file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Object File Did Not Open\n");
        exit(1);
    }
    
    if openErrFile(errFile, errName)
    // Open error file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Error File Did Not Open\n");
        exit(1);
    }
}
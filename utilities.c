// utilites.c
// Arthur Knapp
// AK146316

// Function Descriptions:

// loadOpcodes:
// This function loads opcodes into the opcodeTable struct array. This will be done by opening and reading
// the opcodes file line by line while there are values left to be read. Each time a value is read, it will
// be stored in the opcodeTable struct.

// symbolName:
// This function reads the name of the input assembly file and checks if it has a file extension. If it does,
// the extension name is including the '.' is striped off. If not, nothing is done. Next the extension ".sym"
// is appendend to the name to get the name. In the main function, a file with this extension will be created to
// store the symbol table.

// objectName:
// Same as symbolName except used for object name

// errorName:
// Same as symbolName except used for error name

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
    //OpCodeTable opcodeTable[OPTABLE_SIZE];
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
        fscanf(opcodeFile, "%d %s %c %d", &opCodeTable[i].opcode,
               opCodeTable[i].mnemonic, &opCodeTable[i].format, &opCodeTable[i].numOps);
        // Reads the opcode, mnemonic, the format, and the number of operands from the opcode file and
        // store it in the opcode table.
    }
    
    if closeOpcodeFile(opcodeFile)
    // Close opcodes file. If it doesn't close, print error message and close program.
    {
        fprintf(stderr, "Error: Couldn't Close Opcodes File\n");
        exit(i);
    }
}

char* symbolName(char *asmName)
{
    char *symName;
    // Stores the name of the symbol table file
    int i = ((int)strlen(asmName) - 1);
    // Int variable to store the string length of asmName and loop through it
    int j = i;
    // Int variable to compare to i

    symName = malloc((int)strlen(asmName) + EXTENSION);
    // Allocate memomory to store the name of the file and the extension ".sym"
    
    for findPeriod(asmName, i);
    // Loop through character array until the first '.'
    
    if noExt(i, BEGINNING_OF_STRING)
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
    // Copy the name of the input file into symFile
    
    strcat(symName, ".sym");
    // Append the extension to the end of the file name
    
    return symName;
}

char* objectName(char *asmName)
{
    char *objName;
    // Stores the name of the object file
    int i = ((int)strlen(asmName) - 1);
    // Int variable to store the string length of asmName and loop through it
    int j = i;
    // Int variable to compare to i
    
    objName = malloc((int)strlen(asmName) + EXTENSION);
    // Allocate memomory to store the name of the file and the extension ".sym"
    
    for findPeriod(asmName, i);
    // Loop through character array until the first '.'
    
    if noExt(i, BEGINNING_OF_STRING)
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
    
    strcpy(objName, asmName);
    // Copy the name of the input file into symFile
    
    strcat(objName, ".obj");
    // Append the extension to the end of the file name
    
    return objName;
}

char* errorName(char *asmName)
{
    char *errName;
    // Stores the name of the error file
    int i = ((int)strlen(asmName) - 1);
    // Int variable to store the string length of asmName and loop through it
    int j = i;
    // Int variable to compare to i
    
    errName = malloc((int)strlen(asmName) + EXTENSION);
    // Allocate memomory to store the name of the file and the extension ".sym"
    
    for findPeriod(asmName, i);
    // Loop through character array until the first '.'
    
    if noExt(i, BEGINNING_OF_STRING)
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
    
    strcpy(errName, asmName);
    // Copy the name of the input file into symFile
    
    strcat(errName, ".err");
    // Append the extension to the end of the file name
    
    return errName;
}

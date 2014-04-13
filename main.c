// main.c
// Arthur Knapp
// AK146316

// Function Descriptions:

// main.c:
// This function opens the files that will be read from and written to and calls various functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"
#include "macros.h"

int main(int argc, char * argv[])
{
    FILE *asmFile;
    // Used to reference the input assembly file
    FILE *objFile;
    // Used to reference the output object file
    FILE *symFile;
    // Used to reference the output symbol table file
    FILE *errFile;
    // Used to reference the output error file
    char *symName;
    // Stores the name of the symbol file
    char *objName;
    // Stores the name of the object file
    char *errName;
    // Stores the name of the error file
    
    if openAsmFile(asmFile, argv[1])
    // Open assembly file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Couldn't Open Assembly File\n");
        exit(1);
    }
    
    symName = symbolName(argv[1]);
    objName = objectName(argv[1]);
    errName = errorName(argv[1]);
    
    printf("Symbol Table File Name: %s\n", symName);
    printf("Object File Name: %s\n", objName);
    printf("Error File Name: %s\n", errName);
    
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

    loadOpcodes();
    // Function call to loadOpcodes
    firstPass(asmFile);
    // Function call to firstPass
    errorChecker(asmFile);
    // Function call to errorChecker
    
    return 0;
}


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
    
    if invalidAmountOfCommands(argc)
    // Checks if there are an incorrect amount of commands
    {
        fprintf(stderr, "Error: Incorrect Number Of Commands\n");
        exit(1);
    }
    
    symName = symbolName(argv[1]);
    objName = objectName(argv[1]);
    errName = errorName(argv[1]);
    // Function calls to get correct file names

    initializeTableToNull();
    // Function call to initializeTableToNull
    errorCodes = firstPass(asmFile);
    // Function call to firstPass
    rewind(asmFile);
    loadOpcodes();
    // Function call to loadOpcodes
    errorCodes = secondPass(asmFile);
    
    if isAnError(errorCodes.invalidOpcodeFlag, errorCodes.undefinedLabelFlag, errorCodes.multDefinedLabelFlag)
    // Checks if there is an illegal opcode, undefined label, multiply defined label and makes error file
    {
        rewind(asmFile);
        errorHandler(asmFile, errName, errorCodes.invalidOpcodeFlag,
                     errorCodes.undefinedLabelFlag, errorCodes.multDefinedLabelFlag);
        // Function call to errorChecker
    }
    
    else
    {
        writeTable(symName);
        // Function call to writeTable to write the symbol table to the .sym file
        
        if openObjFile(objFile, objName)
            // Open object file. If it doesn't open, print error message and close program.
        {
            fprintf(stderr, "Error: Object File Did Not Open\n");
            exit(1);
        }
        
        printAssembledValuesList(objFile);
        // Function call to printAssembledValuesList to write the lc values and contents to .obj file
    }

    return 0;
}


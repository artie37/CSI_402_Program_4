// main.c
// Arthur Knapp
// AK146316

#include <stdio.h>
#include "constants.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

int main(int argc, char * argv[])
{
    openFiles(argv[1]);
    // Function call to utilities to open all input and output files
    loadOpcodes();
    // Function call to loadOpcodes to insert the opcodes in to the opcode struct array
    errorChecker();
    // Function call to errorChecker
    return 0;
}


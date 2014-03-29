// macros.h
// Arthur Knapp
// AK146316


// File: utilities.c

// For Loop Conditions:
#define opTableCondition(i) (; (i) < OPTABLE_SIZE; (i)++)
// For loop condition to loop through the opcodes table struct array
#define findPeriod(asmFile, i) (; (asmFile[i] != '.') && ((i) >= 0); (i)--)
// For loop condition to loop through asm file name until '.' is found
#define delExt(i, j) (; (i) < (j); (i)++)
// For loop condition to loop through asm file name until end

// Various If Conditions:
#define noExt(i, j) ((i) == (j))
// Checks if character array index is at the beginning of the array

// Opening Files
#define openOpcodeFile(opcodeFile) ((opcodeFile = fopen("opcodes", "r")) == NULL)
// If condition that opens the opcode file and checks if it doesn't open
#define openAsmFile(asmFile, asmName) ((asmFile = fopen(asmName, "r")) == NULL)
// If condition that opens the assembly file and checks if it doesn't open
#define openSymFile(symFile, symName) ((symFile = fopen(symName, "r")) == NULL)
// If condition that opens the symbol table file and checks if it doesn't open
#define openObjFile(objFile, objName) ((objFile = fopen(objName, "r")) == NULL)
// If condition that opens the object file and checks if it doesn't open
#define openErrFile(errFile, errName) ((errFile = fopen(errName, "r")) == NULL)
// If condition that opens the error file and checks if it doesn't open

// Closing Files
#define closeOpcodeFile(opcodeFile) (fclose(opcodeFile) != 0)
// If condition that closes the opcode file and checks if it doesn't close

//------------------------------------------------------------------------------------------------------------------------------------
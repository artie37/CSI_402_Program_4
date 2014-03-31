// macros.h
// Arthur Knapp
// AK146316

//------------------------------------------------------------------------------------------------------------------------------------

// File: utilities.c

// For Loop Conditions:

#define opTableCondition(i) (; (i) < OPTABLE_SIZE; (i)++)
// Loops through the opcodes table struct array
#define findPeriod(asmFile, i) (; (asmFile[i] != '.') && ((i) >= 0); (i)--)
// Loops through asm file name until '.' is found
#define delExt(i, j) (; (i) < (j); (i)++)
// Loops through asm file name until end

// Various If Conditions:

#define noExt(i, j) ((i) == (j))
// Checks if character array index is at the beginning of the array

// Opening Files:

#define openOpcodeFile(opcodeFile) ((opcodeFile = fopen("opcodes", "r")) == NULL)
// Opens the opcode file and checks if it doesn't open
#define openAsmFile(asmFile, asmName) ((asmFile = fopen(asmName, "r")) == NULL)
// Opens the assembly file and checks if it doesn't open
#define openSymFile(symFile, symName) ((symFile = fopen(symName, "w")) == NULL)
// Opens the symbol table file and checks if it doesn't open
#define openObjFile(objFile, objName) ((objFile = fopen(objName, "w")) == NULL)
// Opens the object file and checks if it doesn't open
#define openErrFile(errFile, errName) ((errFile = fopen(errName, "w")) == NULL)
// Opens the error file and checks if it doesn't open

// Closing Files:

#define closeOpcodeFile(opcodeFile) (fclose(opcodeFile) != 0)
// Closes the opcode file and checks if it doesn't close

//------------------------------------------------------------------------------------------------------------------------------------

// File: functions.c

// Function: errorChecker********************************************************************************

// While Loop Conditions:

#define linesInAsmFile(line, LINE_SIZE, asmFile) (fgets(line, LINE_SIZE, asmFile) != NULL)
// Loops through the source file and stores each line in character array "line"
#define lineNotNull(line, i) (line[i] != '\0')
// Loops through the line character by character until the end of line

// If Statement Conditions:

#define notWhitespace(line, i) ((line[i] != ' ') && (line[i] != '\t') && (line[i] != '\n'))
// Checks if the current character is not a whitespace, tab, or newline character signifying the current
// character is not whitespace.
#define isWhitespace(charFlag) (charFlag == 0)
// Checks if the charFlag remained 0 signifying that the line is whitespace
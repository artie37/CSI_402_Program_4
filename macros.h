// macros.h
// Arthur Knapp
// AK146316

//************************************************************************************************************************************

// File: main.c

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

#define closeAsmFile(asmFile) (fclose(asmFile) != 0)
// Closes the assembly file and checks if it doesn't close
#define closeSymFile(symFile) (fclose(symFile) != 0)
// Closes the symbol table file and checks if it doesn't close
#define closeObjFile(objFile) (fclose(objFile) != 0)
// Closes the object file and checks if it doesn't close
#define closeErrFile(errFile) (fclose(errFile) != 0)
// Closes the error file and checks if it doesn't close

//************************************************************************************************************************************

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

// Closing Files:

#define closeOpcodeFile(opcodeFile) (fclose(opcodeFile) != 0)
// Closes the opcode file and checks if it doesn't close

//************************************************************************************************************************************

// File: functions.c

// Function: firstPass~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// While Loop Conditions

#define tokNotNull(label) (label != NULL)
// Checks if the current token is not null to keep looping

// If Statement Conditions

#define isValidChar(line, i) ((line[i] != ' ') && (line[i] != '\t') && (line[i] != '\n') && (line[i] != '#'))
// Checks if the current character is not a whitespace, tab, newline character, or a '#' signifying the current
// character is not whitespace or a comment symbol.
#define isLabel(token, tokLength) (token[tokLength] == ':')
// Checks if the current token is a label by checking to see if the last character of the token is a ':'
#define isPseudoOp(token) (token[0] == '.')
// Checks if the current token is a pseudo opcode by checking to see if the first character of token is a '.'
#define isResw(token) (strcmp(token, ".resw") == 0)
// Checks if the current token is ".resw"
#define isWord(token) (strcmp(token, ".word") == 0)
// Checks if the current token is ".word"
#define isDataOrText(token) (strcmp(token, ".data") == 0 || strcmp(token, ".text") == 0)
// Checks if the current token is ".data" or ".text"

// Function: secondPass~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// While Loop Conditions:

#define opTable(x) (x <= 35)
// Loops through the opcode table for each entry

// If Statement Conditions:

#define isOpcode(mnemonic, token) (strcmp(mnemonic, token) == 0)
// Checks if the current token is a valid opcode
#define isFirstOperand(numOps) (numOps > 0)
// Checks if there are more than 0 operands
#define isSecondOperand(numOps) (numOps > 1)
// Checks if there are more than 1 operands
#define isThirdOperand(numOps) (numOps > 2)
// Checks if there are more than 2 operands

// Function: errorChecker~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

//************************************************************************************************************************************

// File: hashFunctions.c

// Function: insert~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define isUpperCase(token) ((token[0] >= 65) && (token[0] <= 90))
// Checks if the ascii value of the first character is between 65 and 90 inclusive signifying a upper case character
#define isLowerCase(token) ((token[0] >= 97) && (token[0] <= 122))
// Checks if the ascii value of the first character is between 97 and 122 inclusive signifying a lower case character

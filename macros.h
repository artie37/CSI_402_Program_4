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

// If Statements:

#define isAnError(invalidOpcode, unLabel, multLabel) (invalidOpcode == 1 || unLabel == 1 || multLabel == 1)
// Checks if there is an illegal opcode, undefined label, multiply defined label and makes error file
#define invalidAmountOfCommands(argc) (argc != 2)
// Checks if there are a correct number of arguments

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

#define isComment(line, i) (line[i] == '#')
// Checks if the current character is a comment sign signifying the line is a comment and it should be skipped
#define isValidChar(line, i) ((line[i] != ' ') && (line[i] != '\t') && (line[i] != '\n'))
// Checks if the current character is not a whitespace, tab, or a newline character, signifying the current
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

#define isOpcode(mnemonic, tok) (strcmp(mnemonic, tok) == 0)
// Checks if the current token is a valid opcode
#define isFirstOperand(numOps) (numOps > 0)
// Checks if there are more than 0 operands
#define isSecondOperand(numOps) (numOps > 1)
// Checks if there are more than 1 operands
#define isThirdOperand(numOps) (numOps > 2)
// Checks if there are more than 2 operands
#define isInvalidOpcode(invalidOpcodeFlag) (invalidOpcodeFlag == 1)
// Checks if the current opcode is invalid by checking if the invalidOpcodeFlag is 1
#define isRegister(op) (op == '$') 
// Checks if op is a register
#define isInParenthesis(op) (op == '(')
// Checks if op is in parenthesis
#define isImmediate(op) ((isdigit(op) || ((op == '-'))))
// Checks if op is a immediate
#define isTypeR(format) (format == 'R')
// Checks if opcode is R format
#define isTypeI(format) (format == 'I')
// Checks if opcode is I format
#define isTypeJ(format) (format == 'J')
// Checks if opcode is J format

// Function: errorHandler~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
#define undefinedLabel(flag) (flag == 1)
// Checks if the undefinedLabelFlag is 1 signifying there is an undefined label
#define multDefinedLabel(flag) (flag == 1)
// Checks if the multDefinedLabelFlag is 1 signfying there are multiply defined labels
#define illegalOpcodes(flag) (flag == 1)
// Checks if the illegalOpcodes flag is 1 signifying there is an illegal opcodes

//************************************************************************************************************************************

// File: hashFunctions.c

// Function: initializeTableToNull~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// For Loop Conditions:

#define hashIndex(HASH_SIZE, i) (; i < HASH_SIZE; i++)
// Loops through the hash table indexes

// Function: hashValue~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define isUpperCase(token) ((token[0] >= 65) && (token[0] <= 90))
// Checks if the ascii value of the first character is between 65 and 90 inclusive signifying a upper case character
#define isLowerCase(token) ((token[0] >= 97) && (token[0] <= 122))
// Checks if the ascii value of the first character is between 97 and 122 inclusive signifying a lower case character

// Function: insert~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// If Conditions:

#define hashListIsEmpty(pHead, index) (pHead[index] == NULL)
// Checks if the head pointer is null and creates a new list
#define isSecondNodeHash(pHead, pTail, index) (pHead[index] == pTail[index])
// Checks if the new node is the second node of the list. If the head and tail
// are the same, there is only one node. Insert node into linked list.
#define nextNodeIsNull(next) (next == NULL)
// Checks if the next node is null. If it is, the current node is the last node
// and the new node will be inserted.
#define isMultiplyDefined(currLabel, newLabel) (strcmp(currLabel, newLabel) == 0)
// Checks if the new label has been previously inserted into the hash table


// Function: writeTable~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// If Conditions:

#define currentNodeIsNotNull(pCurr) (pCurr != NULL)
// Checks if the current postion has a list

// While Conditions:

#define nodesInList(pCurr) (pCurr != NULL)
// Loop to the last node in the linked list to insert the new node

// Function: findUndefinedLabel~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// If Conditions:

#define labelIsDefined(pCurr, pLabel, label) ((pCurr != NULL) && (strcmp(pLabel, label) == 0))
// Checks if the label is defined in the assembly file
#define labelIsNotDefined(undefinedFlag) (undefinedFlag == 1)
// Checks if the label was not defined.

//************************************************************************************************************************************

// File: errorLinkedList.c

// Function: All Inserts~~~~~~~~~!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define listIsEmpty(pHead) (pHead == NULL)
// Checks if the head pointer is null and creates a new list
#define isSecondNode(pHead, pTail) (pHead == pTail)
// Checks if the new node is the second node of the list. If the head and tail
// are the same, there is only one node. Insert node into linked list.

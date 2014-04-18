// externs.h
// Arthur Knapp
// AK146316

extern OpCodeTable opCodeTable[OPTABLE_SIZE];
// Used to store the opCodeTable struct array
extern ErrorCodes errorCodes;
// Used to store the error codes from second pass
extern FILE *asmFile;
// Used to reference the input assembly file
extern FILE *objFile;
// Used to reference the output object file
extern FILE *symFile;
// Used to reference the output symbol table file
extern FILE *errFile;
// Used to reference the output error file
extern char *errName;
// Stores the name of the error file
extern char *tok;
// Used to store the label to be entered into the symbol table
extern char *label;
// Stores the label
extern char lineNum;
// Used to store the line number of the error
extern int undefinedLabelFlag;
// Flag signifying whether or not the label is defined. 1 = undefined, 0 = defined.
extern int multDefinedLabelFlag;
// Flag signifying whether or not the label is defined. 1 = undefined, 0 = defined.
extern int invalidOpcodeFlag;
// Flag signifying whether or not the opcode is valid. 1 = invalid, 0 = defined.
extern int opcodeNum;
// Number value of the opcode
extern int sourceReg1;
// Value of source register 1
extern int sourceReg2;
// Value of source register 2
extern int targetReg;
// Value of target register
extern int immediate;
// Value of immediate
extern int lcValue;
// LC Value of insruction
extern int opNum1;
// Stores the contents of an opperand
extern int opNum2;
// Stores the contents of an opperand
// globals.h
// Arthur Knapp
// AK146316

OpCodeTable opCodeTable[OPTABLE_SIZE];
// Used to store the opCodeTable struct array
FILE *asmFile;
// Used to reference the input assembly file
FILE *objFile;
// Used to reference the output object file
FILE *symFile;
// Used to reference the output symbol table file
FILE *errFile;
// Used to reference the output error file
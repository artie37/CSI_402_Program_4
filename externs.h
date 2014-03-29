// externs.h
// Arthur Knapp
// AK146316

extern OpCodeTable opCodeTable[OPTABLE_SIZE];
// Used to store the opCodeTable struct array
extern FILE *asmFile;
// Used to reference the input assembly file
extern FILE *objFile;
// Used to reference the output object file
extern FILE *symFile;
// Used to reference the output symbol table file
extern FILE *errFile;
// Used to reference the output error file
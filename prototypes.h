// prototypes.h
// Arthur Knapp
// AK146316

// File: utilities.c--------------------------------------------------------------------------------------------------------------------------

void loadOpcodes();
char * symbolName(char *);
char * objectName(char *);
char * errorName(char *);

// File: functions.c--------------------------------------------------------------------------------------------------------------------------

void firstPass(FILE *);
void secondPass(FILE *);
void errorChecker(FILE *);

// File: hashFunctions.c----------------------------------------------------------------------------------------------------------------------

int hashValue(char *);
void insert(char *);
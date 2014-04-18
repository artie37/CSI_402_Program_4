// prototypes.h
// Arthur Knapp
// AK146316

// File: utilities.c--------------------------------------------------------------------------------------------------------------------------

void loadOpcodes();
char * symbolName(char *);
char * objectName(char *);
char * errorName(char *);

// File: functions.c--------------------------------------------------------------------------------------------------------------------------

ErrorCodes firstPass(FILE *);
ErrorCodes secondPass(FILE *);
void errorHandler(FILE *, char *, int, int, int);

// File: hashFunctions.c----------------------------------------------------------------------------------------------------------------------

void initializeTableToNull();
int hashValue(char *);
int insert(char *, int);
void createList(char *, int, int);
void writeTable(char *);
int findUndefinedLabel(char *);
int findLabelAddress(char *);

// File: errorLinkedLists.c-------------------------------------------------------------------------------------------------------------------

void insertUndefinedLabel(char *);
void insertMultDefinedLabel(char *);
void insertIllegalOpcode(char *, int);
void createUndefinedLabelList(char *);
void createMultDefinedLabelList(char *);
void createIllegalOpcodeList(char *, int);
void printIllegalOpcodeList(FILE *);
void printUndefinedLabelList(FILE *);
void printMultDefinedLabelList(FILE *);

// File: objectFunctions.c

void assembleR(int, int, int, int, int, int);
void assembleJ(int, int, int, int, char *);
void assembleI();
int assembleResw(int, int);
int assembleWord(int, int, int);
void insertAssembledValues(int, int);
void createAssembledValuesList(int, int);
void printAssembledValuesList(FILE *);

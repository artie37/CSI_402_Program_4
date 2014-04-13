// structs.h
// Arthur Knapp
// AK146316

// Struct Descriptions:

// opcodeTable:
// This struct will be used as an array to store the TMIPS opcode table in memory.
// It stores the integer opcode value, the mnemonic, the format of the opcode, and
// the number of operands.

// SymbolTable:
// This struct will be used as a hash table to store the labels and lc values.
// It stores the name of the label and the lc value.

typedef struct OpCodeTable
{
    int opcode;
    char mnemonic[MNEMONIC_SIZE];
    char format;
    int numOps;
} OpCodeTable;

typedef struct SymbolTable
{
    char name[LABEL_SIZE];
    int lcValue;

    struct SymbolTable *next;
} SymbolTable;
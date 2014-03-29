// structs.h
// Arthur Knapp
// AK146316

// Struct Descriptions:

// opcodeTable:
// This struct will be used as an array to store the TMIPS opcode table in memory.
// It stores the integer value, the mnemonic, and the format of the opcode.

typedef struct OpCodeTable
{
    int opcode;
    char mnemonic[MNEMONIC_SIZE];
    char format;
    
} OpCodeTable;
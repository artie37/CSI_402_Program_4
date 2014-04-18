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

// LinkedListUndefinedLabel:
// This struct will be used as a linked list for undefined labels. It stores the label

// LinkedListMultDefinedLabel:
// This struct will be used as a linked list for multiply defined labels. It stores the label.

// LinkedListIllegalMachineOpcode:
// This struct will be used as a linked list for illegal opcode. It stores the opcode and the
// line number that the illegal opcode occured on.

// ErrorCodes:
// This struct will be used to store the error code flags and return them. These are stored in
// a struct because returning multiple parameters is not permmited.

// AssembledValues:
// This struct will be used as a linked list for assembled values. It stores the lc value of the
// instruction and the contents of the instruction.

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

typedef struct LinkedListUndefinedLabel
{
    char name[LABEL_SIZE];
    
    struct LinkedListUndefinedLabel *next;
}UndefinedLabelList;

typedef struct LinkedListMultDefinedLabel
{
    char name[LABEL_SIZE];
    
    struct LinkedListMultDefinedLabel *next;
}MultDefinedLabelList;

typedef struct LinkedListIllegalMachineOpcode
{
    char mnemonic[MNEMONIC_SIZE];
    int lineNum;
    
    struct LinkedListIllegalMachineOpcode *next;
}IllegalOpcodeList;

typedef struct ErrorCodes
{
    int invalidOpcodeFlag;
    // Flag signifying whether or not the opcode is valid or not. 1 = invalid, 0 = valid.
    int undefinedLabelFlag;
    // Flag signifying whether or not the label is defined. 1 = undefined, 0 = defined.
    int multDefinedLabelFlag;
    // Flag signifying whether or not the label is multiply defined.
    // 1 = multiply defined, 0 = singly defined.
}ErrorCodes;

typedef struct AssembledValues
{
    int lcValue;
    // LC Value of instruction
    int contents;
    // Contents of instruction
    
    struct AssembledValues *next;
}AssembledValues;


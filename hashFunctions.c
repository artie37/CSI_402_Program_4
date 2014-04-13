// hashFunctions.c
// Arthur Knapp
// AK146316

// Functions:

// hashValue:
// Computes the index value the string should be inserted into. This value is found by checking if
// the string token is lower case by checking if the ascii value of the first character is between 97 and 122 inclusive
// or if it is upper case by checking if the ascii value of the first character is between 65 and 90 inclusive. If it
// is lower case, the 97 will be subratcted from the ascii value of the first character to find where it fits between
// 0 and 25 inclusive and for upper case, 65 is subtracted for the same reason. this value is the stored into index and
// returned to where the function was called.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

int hashValue(char *token)
{
    int index;
    // Stores the index value to insert the symbol into the hash table
    if isLowerCase(token)
    // Checks if the first character of the label is lower case
    {
        index = token[0] - 97;
        // Finds the index value based on lower case ascii value
    }
    
    else if isUpperCase(token)
    // Checks if the first character of the label is upper case
    {
        index = token[0] - 65;
        // Finds the index value based on upper case ascii value
    }

    return index;
    // Return the index value
}
void insert(char *token)
{
    SymbolTable *hash[HASH_SIZE];
    // Pointer to access the hash table
    int i = 0;
    // Counter used in the for loop to search the hash table
    int index;
    // Stores the index value to insert the symbol into the hash table
    
    index = hashValue(token);
    // Call the hashValue function to get teh index value of the postion to store
    // the symbol in the hash table. Store this value in index.
    
    
}
// hashFunctions.c
// Arthur Knapp
// AK146316

// Functions:

// initializeTableToNull:
// Initializes all of the head and tail nodes in the hash table to null. This is done by looping through the hash table
// and inserting null into the nodes.

// hashValue:
// Computes the index value the string should be inserted into. This value is found by checking if
// the string token is lower case by checking if the ascii value of the first character is between 97 and 122 inclusive
// or if it is upper case by checking if the ascii value of the first character is between 65 and 90 inclusive. If it
// is lower case, the 97 will be subratcted from the ascii value of the first character to find where it fits between
// 0 and 25 inclusive and for upper case, 65 is subtracted for the same reason. this value is the stored into index and
// returned to where the function was called.

// insert:
// Inserts the label and lc values into the hash table.

// createList:
// Creates a new list in the specified postition of the hash table if the head node is null.

// writeTable:
// Writes lc values and label from the hash table to the symbol table file

// findUndefinedLabel:
// Searches through the hash table comparing each label to the label specified in the char
// pointer tok. If the label specified in tok is not found, 1 is returned signifying the specified
// label is undefined.

// findLabelAddress:
// Searches through the hash table comparing each label to the label specified in the char
// pointer tok. When the specified label is found, the coresponding lc value is returned

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

SymbolTable *pHead[HASH_SIZE];
// Declare an array of pointers. This will be the hash table.
SymbolTable *pTail[HASH_SIZE];

void initializeTableToNull()
{
    int i = 0;
    // Counter usid in the for loop to loop through hash table

    for hashIndex(HASH_SIZE, i)
    // Loop through each index of the hash table
    {
        pHead[i] = NULL;
        pTail[i] = NULL;
        // Insert null into head and tail pointer
    }
}

int hashValue(char *tok)
{
    int index;
    // Stores the index value to insert the symbol into the hash table
    if isLowerCase(tok)
    // Checks if the first character of the label is lower case
    {
        index = tok[0] - LOWER_CASE;
        // Finds the index value based on lower case ascii value
    }
    
    else if isUpperCase(tok)
    // Checks if the first character of the label is upper case
    {
        index = tok[0] - UPPER_CASE;
        // Finds the index value based on upper case ascii value
    }

    return index;
    // Return the index value
}

int insert(char *tok, int lcVal)
{
    int index;
    // Stores the index value to insert the symbol into the hash table
    int multDefinedLabelFlag = 0;
    // Flag signifying whether or not the label is defined. 1 = multiply defined, 0 = singly defined.
    index = hashValue(tok);
    // Call the hashValue function to get teh index value of the postion to store
    // the symbol in the hash table. Store this value in index.
    
    if hashListIsEmpty(pHead, index)
    // Checks if the head pointer is null and creates a new list
    {
        createList(tok, lcVal, index);
        // Call to function createNewList
    }
    
    else
    // If there are pointers in the list.
    {
        SymbolTable *pNewNode = malloc(sizeof(SymbolTable));
        // Create new node to be inserted into the hash table
        SymbolTable *pCurr = pHead[index];
        // Create node to loop through the linked list at the position given by index
        
        strcpy(pNewNode -> name, tok);
        // Insert the symbol into the new node
        pNewNode -> lcValue = lcVal;
        // Insert the lc value of the symbol into the new node
        
        if isSecondNodeHash(pHead, pTail, index)
        // Checks if the new node is the second node of the list. If the head and tail
        // are the same, there is only one node. Insert node into linked list.
        {
            pCurr = pHead[index];
            // Insert pHead[index] into pCurr
            
            if isMultiplyDefined(pCurr -> name, pNewNode -> name)
            // Checks if the new label has been previously inserted into the hash table
            {
                insertMultDefinedLabel(tok);
                // Send the label to function insertMultDefinedLabel to store the multiply defined label to be
                // written to the error file.

                multDefinedLabelFlag = 1;
                // Set flag to 1 signifying there are multiply defined labels
            }
            pHead[index] -> next = pNewNode;
            // Head node points to the new node
            pTail[index] = pNewNode;
            // Insert the new node into the tail pointer
            pTail[index] -> next = NULL;
            // Make tail node point to null to make it the end of the list
        }
        
        else
        // If the current node is not the second node
        {
            while nodesInList(pCurr)
            // Loop to the last node in the linked list to insert the new node
            {
                if isMultiplyDefined(pCurr -> name, pNewNode -> name)
                // Checks if the new label has been previously inserted into the hash table
                {
                    insertMultDefinedLabel(tok);
                    // Send the label to function insertMultDefinedLabel to store the multiply defined label to be
                    // written to the error file.

                    multDefinedLabelFlag = 1;
                    // Set flag to 1 signifying there are multiply defined labels
                }

                if nextNodeIsNull(pCurr -> next)
                // Checks if the next node is null. If it is, the current node is the last node
                // and the new node will be inserted.
                {
                    pCurr -> next = pNewNode;
                    // Insert the new node into the tail pointer
                    pTail[index] = pNewNode;
                    // Current node points to the new node
                    pTail[index] -> next = NULL;
                    // Make tail node pointe to null to make it the end of the list
                    break;
                    // Break out of loop so the last node isn't duplicated
                }
                
                pCurr = pCurr -> next;
                // Move to the next node
            }
        } // End else isSecondNode
        
    } // End else listIsEmpty
    
    return multDefinedLabelFlag;
}

void createList(char *tok, int lcVal, int index)
{
    SymbolTable *pNewNode = malloc(sizeof(SymbolTable));
    // Create new node to be inserted into the hash table
    pNewNode -> next = NULL;
    // Have new node point to null
    
    strcpy(pNewNode -> name, tok);
    pNewNode -> lcValue = lcVal;
    // Insert the label and lc value inte the node
    
    pHead[index] = pTail[index] = pNewNode;
    // Set the head and tail equal to the new node because there is only one node
}

void writeTable(char *symName)
{
    int i = 0;
    // Counter to loop through the hash table index values
    SymbolTable *pCurr;
    // Create node to loop through the linked list at the postion given by i
    FILE *symFile;
    // Used to reference the output symbol table file
    
    if openSymFile(symFile, symName)
        // Open symbol table file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Symbol Table File Did Not Open\n");
        exit(1);
    }


    for hashIndex(HASH_SIZE, i)
    // Loops through index values in the hash table
    {
        
        pCurr = pHead[i];
        // Insert the head node at index i into curr
        
        if currentNodeIsNotNull(pCurr)
        // Checks if the current postion has a list
        {
            
            while nodesInList(pCurr)
            // Loops through the linked list
            {
                    
                fprintf(symFile, "%s\t", pCurr -> name);
                fprintf(symFile, "%d\n", pCurr -> lcValue);
                // Write symbol and lc value to symbol file
                
                pCurr = pCurr -> next;
                // Point to next node
            }
        }
    }
    
    if closeSymFile(symFile)
    {
        fprintf(stderr, "Error: Symbol Table File Did Not Close\n");
        exit(1);
    }
}

int findUndefinedLabel(char *tok)
{
    int index;
    // Stores the index value of search for the label
    int undefinedFlag = 1;
    // Flag signifying whether or not the label is defined. 1 = undefined, 0 = defined.
    SymbolTable *pCurr;
    // Declare node to loop through the list at a given index
    
    index = hashValue(tok);
    // Get the index value of the postion of the linked list to search through
    
    pCurr = pHead[index];
    // Insert the head node at the index value
    
    while nodesInList(pCurr)
    // Loop through the list while there are nodes in the list
    {
        if labelIsDefined(pCurr, pCurr -> name, tok)
        // Checks if the label equals the label in the current node
        {
            undefinedFlag = 0;
            // Set to 0 signifying that the label was defined
            
            break;
            // Break out of loop
        }
        pCurr = pCurr -> next;
        // Move to the next node
    }
    
    if labelIsNotDefined(undefinedFlag)
    // Checks to see if the label was defined by checking the flag. If not, send to linked list that
    // stores undefined labels.
    {
        insertUndefinedLabel(tok);
        // Send the label to function insertUndefinedLabel to store the undefined label to be
        // written to the error file.
    }
    
    return undefinedFlag;
}

int findLabelAddress(char *tok)
{
    int index;
    // Stores the index value of search for the label
    int labelAddress;
    // Stores the label address
    SymbolTable *pCurr;
    // Declare node to loop through the list at a given index
    
    index = hashValue(tok);
    // Get the index value of the postion of the linked list to search through
    
    pCurr = pHead[index];
    // Insert the head node at the index value
    
    while nodesInList(pCurr)
    // Loop through the list while there are nodes in the list
    {
        if labelIsDefined(pCurr, pCurr -> name, tok)
        // Checks if the label equals the label in the current node
        {
            labelAddress = pCurr -> lcValue;
            // Insert lcValue into label address
            
            break;
            // Break out of loop
        }
        pCurr = pCurr -> next;
        // Move to the next node
    }
    
    return labelAddress;
}
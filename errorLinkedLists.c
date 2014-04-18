// errorLinkedLists.c
// Arthur Knapp
// AK146316

// Functions:

// insertUndefinedLabel:
// Inserts the label into the undefined label linked list

// insertMultDefinedLinked:
// Inserts the label into the multiply defined label linked list

// insertIllegalOpcode
// Inserts the opcode and the line number into illegal opcode linked list

// createUndefinedLabelList
// Creates the list to store undefined labels

// createMultDefinedLabelList:
// Creates the list to store multiply defined labels

// createIllegalOpcodeList
// Creates the list to store illegal opcodes

// printUndefinedLabelList
// Prints the list to store undefined labels

// printMultDefinedLabelList:
// Prints the list to store multiply defined labels

// printIllegalOpcodeList
// Prints the list to store illegal opcodes


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

UndefinedLabelList *pHeadUnDef = NULL;
UndefinedLabelList *pTailUnDef = NULL;
// Define head and tail nodes for UndefinedLabelList

MultDefinedLabelList *pHeadMultDef = NULL;
MultDefinedLabelList *pTailMultDef = NULL;
// Define head and tail nodes for MultDefinedLabelList

IllegalOpcodeList *pHeadIllOpcode = NULL;
IllegalOpcodeList *pTailIllOpcode = NULL;
// Define head and tail nodes for IllegalOpcodeList

void insertUndefinedLabel(char *label)
{
    if listIsEmpty(pHeadUnDef)
    {
        createUndefinedLabelList(label);
        // Call createIllegalOpcode to create list
    }
    
    else
    // List is not empty
    {
        UndefinedLabelList *pNewNode = malloc(sizeof(UndefinedLabelList));
        // Create new node to be inserted into the linked list
        UndefinedLabelList *pCurr = pHeadUnDef;
        // Create node to loop through the linked list
        
        strcpy(pNewNode -> name, label);
        // Insert the opcode into the new node
        
        if isSecondNode(pHeadUnDef, pTailUnDef)
            // Checks if the new node is the second node of the list. If the head and tail
            // are the same, there is only one node. Insert node into linked list.
        {
            pHeadUnDef -> next = pNewNode;
            // Head node points to the new node
            pTailUnDef = pNewNode;
            // Insert the new node into the tail pointer
            pTailUnDef -> next = NULL;
            // Make the tail node point to null to make it the end of the list
        }
        
        else
            // If the current node is not the second node
        {
            while nodesInList(pCurr)
                // Loop to the last node in the linked list to insert the new node
            {
                if nextNodeIsNull(pCurr -> next)
                    // Checks if teh next node is null. If it is, the current node is the last node
                    // and the new node will be inserted.
                {
                    pCurr -> next = pNewNode;
                    // Current node points to the new node
                    pTailUnDef = pNewNode;
                    // Insert the new node into the tail pointer
                    pTailUnDef -> next = NULL;
                    // make tail node point to null to make it the end of the list
                    break;
                    // Break out of loop so the last node isn't duplicated
                }
                
                pCurr = pCurr -> next;
                // Move to the next node
            } // End while nodesInList
        } // End else isSecondNode
        
    }// End else listIsEmpty
}

void insertMultDefinedLabel(char *label)
{
    if listIsEmpty(pHeadMultDef)
    {
        createMultDefinedLabelList(label);
        // Call createIllegalOpcode to create list
    }
    
    else
        // List is not empty
    {
        MultDefinedLabelList *pNewNode = malloc(sizeof(MultDefinedLabelList));
        // Create new node to be inserted into the linked list
        MultDefinedLabelList *pCurr = pHeadMultDef;
        // Create node to loop through the linked list
        
        strcpy(pNewNode -> name, label);
        // Insert the opcode into the new node
        
        if isSecondNode(pHeadMultDef, pTailMultDef)
        // Checks if the new node is the second node of the list. If the head and tail
        // are the same, there is only one node. Insert node into linked list.
        {
            pHeadMultDef -> next = pNewNode;
            // Head node points to the new node
            pTailMultDef = pNewNode;
            // Insert the new node into the tail pointer
            pTailMultDef -> next = NULL;
            // Make the tail node point to null to make it the end of the list
        }
        
        else
        // If the current node is not the second node
        {
            while nodesInList(pCurr)
            // Loop to the last node in the linked list to insert the new node
            {
                if nextNodeIsNull(pCurr -> next)
                // Checks if teh next node is null. If it is, the current node is the last node
                // and the new node will be inserted.
                {
                    pCurr -> next = pNewNode;
                    // Current node points to the new node
                    pTailMultDef = pNewNode;
                    // Insert the new node into the tail pointer
                    pTailMultDef -> next = NULL;
                    // make tail node point to null to make it the end of the list
                }
                
                pCurr = pCurr -> next;
                // Move to the next node
            } // End while nodesInList
        } // End else isSecondNode
        
    }// End else listIsEmpty
}

void insertIllegalOpcode(char *opCode, int line)
{
    if listIsEmpty(pHeadIllOpcode)
    {
        createIllegalOpcodeList(opCode, line);
        // Call createIllegalOpcode to create list
    }
    
    else
    // List is not empty
    {
        IllegalOpcodeList *pNewNode = malloc(sizeof(IllegalOpcodeList));
        // Create new node to be inserted into the linked list
        IllegalOpcodeList *pCurr = pHeadIllOpcode;
        // Create node to loop through the linked list
        
        strcpy(pNewNode -> mnemonic, opCode);
        // Insert the opcode into the new node
        pNewNode -> lineNum = line;
        // Insert the line number into the new node
        
        if isSecondNode(pHeadIllOpcode, pTailIllOpcode)
        // Checks if the new node is the second node of the list. If the head and tail
        // are the same, there is only one node. Insert node into linked list.
        {
            pHeadIllOpcode -> next = pNewNode;
            // Head node points to the new node
            pTailIllOpcode = pNewNode;
            // Insert the new node into the tail pointer
            pTailIllOpcode -> next = NULL;
            // Make the tail node point to null to make it the end of the list
        }
        
        else
        // If the current node is not the second node
        {
            while nodesInList(pCurr)
            // Loop to the last node in the linked list to insert the new node
            {
                if nextNodeIsNull(pCurr -> next)
                // Checks if teh next node is null. If it is, the current node is the last node
                // and the new node will be inserted.
                {
                    pCurr -> next = pNewNode;
                    // Current node points to the new node
                    pTailIllOpcode = pNewNode;
                    // Insert the new node into the tail pointer
                    pTailIllOpcode -> next = NULL;
                    // make tail node point to null to make it the end of the list
                }
                
                pCurr = pCurr -> next;
                // Move to the next node
            } // End while nodesInList
        } // End else isSecondNode
        
    }// End else listIsEmpty
    
}

void createUndefinedLabelList(char *label)
{
    UndefinedLabelList *pNewNode = malloc(sizeof(UndefinedLabelList));
    // Create new node to be inserted into the list
    pNewNode -> next = NULL;
    // Have new node point to null
    
    strcpy(pNewNode -> name, label);
    // Insert the label into the new node
    
    pHeadUnDef = pTailUnDef = pNewNode;
    // Set the head and tail equal to the new node because there is only one node
}

void createMultDefinedLabelList(char *label)
{
    MultDefinedLabelList *pNewNode = malloc(sizeof(MultDefinedLabelList));
    // Create new node to be inserted into the list
    pNewNode -> next = NULL;
    // Have new node point to null
    
    strcpy(pNewNode -> name, label);
    // Insert the label into the new node
    
    pHeadMultDef = pTailMultDef = pNewNode;
    // Set the head and tail equal to the new node because there is only one node
}

void createIllegalOpcodeList(char *opCode, int line)
{
    IllegalOpcodeList *pNewNode = malloc(sizeof(IllegalOpcodeList));
    // Create new node to be inserted into the list
    pNewNode -> next = NULL;
    // Have new node point to null
    
    strcpy(pNewNode -> mnemonic, opCode);
    // Insert the label into the new node
    pNewNode -> lineNum = line;
    // Insert the line number into the new node
    
    pHeadIllOpcode = pTailIllOpcode = pNewNode;
    // Set the head and tail equal to the new node because there is only one node
}

void printUndefinedLabelList(FILE *errFile)
{
    UndefinedLabelList *pCurr = pHeadUnDef;
    // Create node to loop through the linked list
    
    while nodesInList(pCurr)
        // Loops through the linked list
    {
        fprintf(errFile, "\t%s\n", pCurr -> name);
        
        pCurr = pCurr -> next;
        // Point to the next node
    }
    
    fprintf(errFile, "\n");
}

void printMultDefinedLabelList(FILE *errFile)
{
    MultDefinedLabelList *pCurr = pHeadMultDef;
    // Create node to loop through the linked list
    
    while nodesInList(pCurr)
        // Loops through the linked list
    {
        fprintf(errFile, "\t%s\n", pCurr -> name);
        
        pCurr = pCurr -> next;
        // Point to the next node
    }
}

void printIllegalOpcodeList(FILE *errFile)
{
    IllegalOpcodeList *pCurr = pHeadIllOpcode;
    // Create node to loop through the linked list
    
    while nodesInList(pCurr)
    // Loops through the linked list
    {
        fprintf(errFile, "\tLine %d:   ", pCurr -> lineNum);
        fprintf(errFile, "Illegal Opcode: %s\n", pCurr -> mnemonic);
        
        pCurr = pCurr -> next;
        // Point to the next node
    }
    
    fprintf(errFile, "\n");
}

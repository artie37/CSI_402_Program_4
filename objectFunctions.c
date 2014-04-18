// objectFunctions.c
// Arthur Knapp
// AK146316

// Functions:

// assembleR:
// This function assembles the r format instructions. This is done by shifting each value into the specified
// position. After the instruction is assembled, the assembled value is sent to the assembled values linked list.

// assembleJ:
// This function assembles the j format instructions. This is done by shifting each value into the specified
// position. After the instruction is assembled, the assembeld value is sent to the assembled values linked list.

// assembleI:
// This function assembles the i format instructions. This is done by shifting each value into the specified
// position. Whether or not the immediate value is a positive or a negative number must be taken into account.
// After the instruction is assembled, the assembeld value is sent to the assembled values linked list.

// assembleResw:
// This function assembles the .resw directive. To assemble this instruction, a word is initialized an amount
// of times specified by immediate. Next, the lc value is returned so it doesn't move ahead of the lc value
// in the function secondPass.

// assembleWord:
// This function assembles the .word directive. In TMIPS, a word is stored in memory in little endian. To do this,
// the order of the bytes that make up the number must be flipped. After the bytes are flipped, a for loop is used
// to insert the value into the assembled values linked list 'opNum2' times. Next, the lc value is returned so it
// doesn't move ahead of the lc value in the function secondPass.

// insertAssembledValues
// Inserts the assembled values into the assembled values linked list

// createAssembledValuesList
// Creates the list to store assembled values

// printAssembledValuesList
// Prints the list to store assembled values


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

AssembledValues *pHeadAssm = NULL;
AssembledValues *pTailAssm = NULL;
// Define head and tail nodes for AssembledValues


void assembleR(int lcVal, int opcodeNum, int sourceReg1, int sourceReg2, int targetReg, int shiftAmt)
{
    int assembledValue = 0;
    // Initialize assembled value to 0
    
    opcodeNum = opcodeNum << FIRST_SHIFT;
    // Shift opcodeNum left 26 bits
    assembledValue = opcodeNum | assembledValue;
    // Bitwise or opcodeNum and assembledValue and store in assembledValue
    sourceReg1 = sourceReg1 << SECOND_SHIFT;
    // Shift sourceReg1 left 21
    assembledValue = sourceReg1 | assembledValue;
    // Bitwise or sourceReg1 and assembledValue and store in assembledValue
    sourceReg2 = sourceReg2 << THIRD_SHIFT;
    // Shift sourceReg2 left 16
    assembledValue = sourceReg2 | assembledValue;
    // Bitwise or sourceReg2 and assembledValue and store in assembledValue
    targetReg = targetReg << FOURTH_SHIFT;
    // Shift targetReg left 11
    assembledValue = targetReg | assembledValue;
    // Bitwise or targetReg and assembledValue and store in assembledValue
    shiftAmt = shiftAmt << FIFTH_SHIFT;
    // Shift shiftAmt left 6
    assembledValue = shiftAmt | assembledValue;
    // Bitwise or shiftAmt and assembledValue and store in assembledValue
    
    insertAssembledValues(lcVal, assembledValue);
    // Call to function insertAssembledValues to insert lcVal and finalValue into
    // the linked list.
}

void assembleJ(int lcVal, int opcodeNum, int sourceReg1, int targetReg, char *label)
{
    int finalValue = 0;
    // Stores the final value
    int address;
    // Stores the address of the label
    
    address = findLabelAddress(label);
    // Finds the address of the label and inserts it into address
    
    opcodeNum <<= FIRST_SHIFT;
    finalValue |= opcodeNum;
    sourceReg1 <<= SECOND_SHIFT;
    finalValue |= sourceReg1;
    targetReg <<= THIRD_SHIFT;
    finalValue |= targetReg;
    finalValue |= address;
    
    insertAssembledValues(lcVal, finalValue);
    // Call to function insertAssembledValues to insert lcVal and finalValue into
    // the linked list.
}

void assembleI(int lcVal, int opcodeNum, int sourceReg1, int targetReg, int immediate)
{
    int finalValue = 0;
    // Stores the final value
    int mask1 = 1;
    // Stores the first mask that is used
    int mask2;
    // Stores the second mask that is used
    
    opcodeNum <<= FIRST_SHIFT;
    finalValue |= opcodeNum;
    sourceReg1 <<= SECOND_SHIFT;
    finalValue |= sourceReg1;
    targetReg <<= THIRD_SHIFT;
    finalValue |= targetReg;
    mask1 <<= SHIFT_THIRTY_ONE;
    // Shift mask1 left 31
    mask2 = mask1 & immediate;
    // And mask1 and immediate and store in mask2
    
    if (mask2 > 0)
    // Checks if mask2 is greater greater than 0 signifying the sign bit is on
    // and the number is negative.
    {
        mask1 = 1;
        // Set mask1 to 1
        mask1 <<= SHIFT_FIFTEEN;
        // Shift left 15
        immediate |= mask1;
        // Or immediate and mask1 and store in immediate
        mask1 = NEGATIVE_NUMBER;
        // Set mask1 to 65535
    }
    
    else
    // The sign bit was 0 signifying the number is positive
    {
        mask1 = POSITIVE_NUMBER;
        // Ensures the proper bits are on and off
    }
    
    immediate = immediate & mask1;
    // And immediate and mask1 and store in immediate
    
    finalValue |= immediate;
    // Or finalValue and immediate and store in finalValue
    
    insertAssembledValues(lcVal, finalValue);
    // Call to function insertAssembledValues to insert lcVal and finalValue into
    // the linked list.
}

int assembleResw(int lcVal, int immediate)
{
    int i = 0;
    // Counter to loop through for loop
    
    for (; i < immediate; i++)
    // Print 0 while immediate is greater than 0
    {
        insertAssembledValues(lcVal, 0);
        // Call to function insertAssembledValues to insert lcVal and finalValue into
        // the linked list.
        
        lcVal++;
        // Increment lc value
    }
    
    return lcVal;
    // Return lc value after it is incremented
}

int assembleWord(int lcVal, int opNum1, int opNum2)
{
    int i = 0;
    unsigned int mask1 = SET_MASK;
    // Stores the first mask
    unsigned int mask2;
    // Stores the second mask that is made
    int finalValue = 0;
    // Stores the final value

    mask1 <<= SHIFT_TWENTYFOUR;
    // Shift mask1 left 24
    mask2 = opNum1 & mask1;
    // And opNum1 and mask1 and store in mask2
    mask2 >>= SHIFT_TWENTYFOUR;
    // Shift mask2 right 24
    finalValue |= mask2;
    // Or finalValue and mask2 and store in finalValue
    mask1 >>= SHIFT_EIGHT;
    // Shift mask1 right 8
    mask2 = opNum1 & mask1;
    // And opNum1 and mask1 and store in mask2
    mask2 >>= SHIFT_EIGHT;
    // Shitf mask2 right 8
    finalValue |= mask2;
    // Or finalValue and mask2 and store in finalValue
    mask1 >>= SHIFT_EIGHT;
    // Shift mask1 right 8
    mask2 = opNum1 & mask1;
    // And mask2 and opNum1 and store in mask2
    mask2 <<= SHIFT_EIGHT;
    // Shift mask2 left 8
    finalValue |= mask2;
    // Or finalValue and mask2 and store in finalValue
    mask1 >>= SHIFT_EIGHT;
    // Shift mask1 right 8
    mask2 = opNum1 & mask1;
    // And mask2 and opNum1 and store in mask2
    mask2 <<= SHIFT_TWENTYFOUR;
    // Shift mask2 left 24
    finalValue |= mask2;
    // Or finalValue and mask2 and store in finalValue
    
    for (; i < opNum2; i++)
    // Print 0 while immediate is greater than 0
    {
        insertAssembledValues(lcVal, finalValue);
        
        lcVal++;
    }

    
    return lcVal;
}

void insertAssembledValues(int lcValue, int assembledValue)
{
    if listIsEmpty(pHeadAssm)
    {
        createAssembledValuesList(lcValue, assembledValue);
        // Call createIllegalOpcode to create list
    }
    
    else
    // List is not empty
    {
        AssembledValues *pNewNode = malloc(sizeof(AssembledValues));
        // Create new node to be inserted into the linked list
        AssembledValues *pCurr = pHeadAssm;
        // Create node to loop through the linked list

        pNewNode -> lcValue = lcValue;
        // Insert lcValue into node
        pNewNode -> contents = assembledValue;
        // Insert assembledValue into node

        if isSecondNode(pHeadAssm, pTailAssm)
        // Checks if the new node is the second node of the list. If the head and tail
        // are the same, there is only one node. Insert node into linked list.
        {
            pHeadAssm -> next = pNewNode;
            // Head node points to the new node
            pTailAssm = pNewNode;
            // Insert the new node into the tail pointer
            pTailAssm -> next = NULL;
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
                    pTailAssm = pNewNode;
                    // Insert the new node into the tail pointer
                    pTailAssm -> next = NULL;
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

void createAssembledValuesList(int lcValue, int assembledValue)
{
    AssembledValues *pNewNode = malloc(sizeof(AssembledValues));
    // Create new node to be inserted into the list
    pNewNode -> next = NULL;
    // Have new node point to null
    pNewNode -> lcValue = lcValue;
    // Insert lcValue into node
    pNewNode -> contents = assembledValue;
    // Insert assembledValue into node

    pHeadAssm = pTailAssm = pNewNode;
    // Set the head and tail equal to the new node because there is only one node
}

void printAssembledValuesList(FILE *objFile)
{
    AssembledValues *pCurr = pHeadAssm;
    // Create node to loop through the linked list
    
    while nodesInList(pCurr)
    // Loops through the linked list
    {
        fprintf(objFile, "%X\t%X\n", pCurr -> lcValue, pCurr -> contents);
        
        pCurr = pCurr -> next;
        // Point to the next node
    }
}


// functions.c
// Arthur Knapp
// AK146316

// Functions:

// firstPass:
// This function makes the first pass through the assembly file and finds values to be inserted into
// the symbol table. This function first loops through the file using fgets to store each line in a
// character array. Next, if the line is not whitespace or a comment, the line is split into tokens with
// the delimiter, " ". If the token ends with ':', then the token is a label and it's LC Value is inserted
// into the hash table that stores the symbol table. After insertion, the next token is taken. The next
// token will either be a pseudo opcode code, or an opcode. If the token begins with a '.' period, it is
// a pseudo opcode; otherwise, it is a regular opcode. For both, the LC Value is incremented and the
// function will go to the top of the loop and check the next line.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

void firstPass(FILE *asmFile)
{
    char line[LINE_SIZE];
    // Stores a line from the source file
    char *token;
    // Stores the string token
    int tokLength;
    // Stores the length of the string token
    int i = 0;
    // Counter to loop through each "line" character array
    int charFlag;
    // Flag signifying whether or not the line had a non whitespace character
    int lcVal = 0;
    // Stores total lc value

    while linesInAsmFile(line, LINE_SIZE, asmFile)
    // Loops through the source file and stores each line in the character array "line"
    {
        charFlag = 0;
        // Set flag to 0 signifying that no non whitespace characters where found
        
        while lineNotNull(line, i)
        // Loops through "line" character by character
        {
            if isValidChar(line, i)
            // Checks if the current character is not a whitespace, tab, newline character, or comment sign signifying
            // the current line is valid.
            {
                charFlag = 1;
                // Set flag to 1 signifying that a non whitespace character was found
                
                token = strtok(line, " ");
                // Get the token for the potential label
                
                tokLength = (int)strlen(token) - 1;
                // Get the last index of token by subracting 1 from the length
                
                if isLabel(token, tokLength)
                // Checks if the current token is a label by checking if the last character of token is a ':'
                {
                    token[tokLength] = '\0';
                    // Strip of the semi colon by inserting a null into the last positon of token
                    
                    // INSERT LABEL AND LC VALUE INTO HASH TABLE
                    
                    token = strtok(NULL, " \t");
                    // Get next token
                }// End if isLabel
                
                if isPseudoOp(token)
                // Checks if the current token is a pseudo opcode by checking if the first character of
                // token is a '.'.
                {
                    if isResw(token)
                    // Checks if token is ".resw"
                    {
                        token = strtok(NULL, " \t\n");
                        // Get next token
        
                        lcVal += atoi(token);
                        // Add the number to the lc value
                    }
                    
                    else if isWord(token)
                    // Checks if token is ".word"
                    {
                        strtok(NULL, " :\t");
                        // Discard the number before the colon
                        token = strtok(NULL, " \t\n");
                        // Store the number after the colon
                        
                        lcVal += atoi(token);
                        // Add the number to the lc value
                    }
                    
                    else if isDataOrText(token)
                    // Checks if token is ".data" or ".text". If true, skip this token.
                    {}
                }// End if PseudoOp
                
                else
                // Token is opcode
                {
                    lcVal += 1;
                    // Add one to the lc value
                }
                
                i = 0;
                // Reset to 0 so character array starts at the beginning of the next line
                break;
                // Break out of while loop to go to next line
            }// End if isValidChar
            
            i++;
            // Increment character array position counter
        }// End while lineNotNull
        
        if isWhitespace(charFlag)
        // If the line is all whitespace or a comment
        {
            i = 0;
            // Reset to 0 so character array starts at the beginning of the next line
        }
    }// End while linesInAsmFile
}

void secondPass(FILE *asmFile)
{
    int x = 0;
    // Counter to search through opcode table
    int i = 0;
    // Counter to loop through each "line" character array
    int opNum;
    // Stores the number in the opperand
    int opNum1;
    // Stores the number in the first operand
    int opNum2;
    // Stores the number in the second operand
    int opNum3;
    // Stores the number in the thrid operand
    int charFlag;
    // Flag signifying whether or not the line had a non whitespace character
    int tokLength;
    // Stores the length of each string token
    char *token;
    // Storaes the string token
    char *op1;
    // Stores the first operand
    char *op2;
    // Stores the second operand
    char *op3;
    // Stores the third operand
    char line[LINE_SIZE];
    // Stores a line from the source
    
    while linesInAsmFile(line, LINE_SIZE, asmFile)
    // Loops through the source file and stores each line in the character array "line"
    {
        charFlag = 0;
        // Set flag to 0 signifying that no non whitespace characters where found
        
        while lineNotNull(line, i)
        // Loops through "line" character by character
        {
            if isValidChar(line, i);
            {
                charFlag = 1;
                // Set flag to 1 signifying that a non whitespace character was found
                
                token = strtok(line, " \t");
                // Get the token for the potential label
                
                tokLength = (int)strlen(token) - 1;
                // Get the last index of the token by subtracting 1 from the length.
                
                if isLabel(token, tokLength)
                // Checks if the current token is a label by checking if the last character of token is a ':'
                {
                    token = strtok(NULL, " \t\n");
                    // Get the next token
                }// End if isLabel
                
                // token = strtok(NULL, " \t\n"); ???????????????????????????
                
                if isPseudoOp(token)
                // Checks if the current token is a pseudo opcode by checking if the first character of
                // token is a '.'.
                {
                    if isResw(token)
                    // Checks if the token is ".resw"
                    {
                        token = strtok(NULL, " \t\n");
                        // Get the next token which is the opperand
                        opNum = atoi(token);
                        // Convert the opperand to an integer
                        
                        // Send to ".resw" function
                    }// End if isResw
                    
                    else if isWord(token)
                    // Checks if the token is ".word"
                    {
                        op1 = strtok(NULL, " \t\n:");
                        // Get the next token which is the first opperand
                        opNum1 = atoi(token);
                        // Convert the opperand to an integer
                        
                        op2 = strtok(NULL, " \t\n:");
                        // Get the noxt token which is the second opperand
                        opNum2 = atoi(token);
                        // Convert the opperand to an integer
                        
                        // Send numbers to to ".word" function
                    }// End if isWord
                }// End if isPseudoOp
                
                else
                // Runs if the token is a normal opcode
                {
                    while opTable(x)
                    // Loops through the opcode table for each entry
                    {
                        if isOpcode(opCodeTable[i].mnemonic, token)
                        // Checks if the current token is a valid opcode
                        {
                            if isFirstOperand(opCodeTable[i].numOps)
                            // Checks if there are more than 0 operands
                            {
                                op1 = strtok(NULL, " ,\t\n");
                                // Get the first operand
                                
                                opNum1 = atoi(op1);
                                // Convert first operand to an integer
                            }
                            
                            if isSecondOperand(opCodeTable[i].numOps)
                            // Checks if there are more than 1 operands
                            {
                                op2 = strtok(NULL, " ,\t\n");
                                // Get the second operand
                                
                                opNum2 = atoi(op2);
                                // Convert second operand to an integer
                            }
                            
                            if isThirdOperand(opCodeTable[i].numOps)
                            // Checks if there are more than 2 operands
                            {
                                op3 = strtok(NULL, " ,\t\n");
                                // Get the third operand
                                
                                opNum3 = atoi(op3);
                                // Convert third opreand to an integer
                            }
                            
                            
                        }// End if isOPcode
                        
                        x++;
                        // Increment while loop counter
                    }// End while opTable
                }// End else opcode
            }// End if isValidChar
        }// End while lineNotNull
    }// End while linesInAsmFile
    
}

void errorChecker(FILE *asmFile)
{
    char line[LINE_SIZE];
    // Stores a line from the source file
    int i = 0;
    // Counter to loop through each "line" character array
    int charFlag;
    // Flag signifying whether or not the line had a non whitespace character
    int lineNum = 0;
    // Counter to store the number of lines with non whitespace characters
    
    while linesInAsmFile(line, LINE_SIZE, asmFile)
    // Loops through the source file and stores each line in the character array "line"
    {
        charFlag = 0;
        // Set flag to 0 signifying that no non whitespace characters were found
        
        lineNum++;
        // Increment line number counter
        
        while lineNotNull(line, i)
        // Loops through "line" character by character
        {
            if notWhitespace(line, i)
            // Checks if the current character is not a whitespace, tab, or newline character signifying the current
            // character is not whitespace. If true, write line number and line to error file.
            {
                
                printf("%d\t%s", lineNum, line);

                i = 0;
                // Reset to 0 so character array starts at the beginning of the next line
            
                charFlag = 1;
                // Set flag to 1 signifying that a non whitespace character was found
            
                break;
                // Break out of while loop so the line isn't written for ever non whitespace character
            }
        
            i++;
            // Increment character array position counter
        }
        
        if isWhitespace(charFlag)
        // If the line is all whitespace, write a newline character to the output file
        {
            printf("%d%s", lineNum, "\n");
            
            i = 0;
            // Reset to 0 so character array starts at the beginning of the next line
        }
    }
}

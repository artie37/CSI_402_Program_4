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

// secondPass:
// This function is similar to firstPass except it checks for errors in the assembly file and sends instructions to
// be assembled. It reads through the assembly file line by line using fgets and reads the line for labels and
// instructions. If it finds an instruction, it checks if it either a .resw or .word directive or if its a normal opcode
// and sends them to the proper functions to be assembled. The struct ErrorCodes is returned.

// errorHandler:
// This function handles errors detected in the assembly file. If an error is occured, the assembly file with line numbers
// will be writen to the error file. Next, the flags for illegal opcodes, undefined labels, and multiply defined labels
// are checked. If any of these flags == 1, the coresponding errors will be printed. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

ErrorCodes firstPass(FILE *asmFile)
{
    char line[LINE_SIZE];
    // Stores a line from the source file
    char *tok;
    // Stores the string token
    int tokLength;
    // Stores the length of the string token
    int i = 0;
    // Counter to loop through each "line" character array
    int charFlag;
    // Flag signifying whether or not the line had a non whitespace character
    int lcVal = 0;
    // Stores total lc value
    int multDefinedLabelFlag;
    // Flag signifying whether or not the label is defined. 1 = undefined, 0 = defined.

    while linesInAsmFile(line, LINE_SIZE, asmFile)
    // Loops through the source file and stores each line in the character array "line"
    {
        charFlag = 0;
        // Set flag to 0 signifying that no non whitespace characters where found
        
        while lineNotNull(line, i)
        // Loops through "line" character by character
        {
            if isComment(line, i)
            // Checks if the current character is a '#' signifying that the line is a comment meaning that the line
            // will be skipped.
            {
                i = 0;
                // Reset counter to 0
                break;
                // Break out of loop to go to the next line
            }
            if isValidChar(line, i)
            // Checks if the current character is not a whitespace, tab, or newline character, signifying
            // the current line is valid.
            {
                charFlag = 1;
                // Set flag to 1 signifying that a non whitespace character was found
                
                tok = strtok(line, " ");
                // Get the token for the potential label
                
                tokLength = (int)strlen(tok) - 1;
                // Get the last index of token by subracting 1 from the length
                
                if isLabel(tok, tokLength)
                // Checks if the current token is a label by checking if the last character of token is a ':'
                {
                    tok[tokLength] = '\0';
                    // Strip of the semi colon by inserting a null into the last positon of token
                    
                    multDefinedLabelFlag = insert(tok, lcVal);
                    // Insert Label and LC value into hashtable
                    
                    if multDefinedLabel(multDefinedLabelFlag)
                    // Checks if label is multiply defined and set flag
                    {
                        errorCodes.multDefinedLabelFlag = multDefinedLabelFlag;
                    }
                    
                    tok = strtok(NULL, " \t");
                    // Get next token
                }// End if isLabel
                
                if isPseudoOp(tok)
                // Checks if the current token is a pseudo opcode by checking if the first character of
                // token is a '.'.
                {
                    if isResw(tok)
                    // Checks if token is ".resw"
                    {
                        tok = strtok(NULL, " \t\n");
                        // Get next token
        
                        lcVal += atoi(tok);
                        // Add the number to the lc value
                    }
                    
                    else if isWord(tok)
                    // Checks if token is ".word"
                    {
                        strtok(NULL, " :\t");
                        // Discard the number before the colon
                        tok = strtok(NULL, " \t\n");
                        // Store the number after the colon
                        
                        lcVal += atoi(tok);
                        // Add the number to the lc value
                    }
                    
                    else if isDataOrText(tok)
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
    
    return errorCodes;
}

ErrorCodes secondPass(FILE *asmFile)
{
    int x = 0;
    // Counter to search through opcode table
    int i = 0;
    // Counter to loop through each "line" character array
    int lcVal = 0;
    // Stores the lc value
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
    int lineNum = 0;
    // Stores the current line number of the assembly file
    int invalidOpcodeFlag = 1;
    // Flag signifying whether or not the opcode is valid or not
    int sourceReg1 = 0;
    // Value of source register 1
    int sourceReg2 = 0;
    // Value of source register 2
    int targetReg = 0;
    // Value of target register
    int immediate = 0;
    // Value of shift amount is 0 by default
    int op1Flag = 0;
    int op2Flag = 0;
    int op3Flag = 0;
    char *tok;
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
        
        lineNum++;
        // Increment line number counter
        
        while lineNotNull(line, i)
        // Loops through "line" character by character
        {
            if isComment(line, i)
            // Checks if the current character is a '#' signifying that the line is a comment meaning that the line
            // will be skipped.
            {
                i = 0;
                // Reset counter to 0
                break;
                // Break out of loop to go to the next line
            }

            if ((line[i] != ' ') && (line[i] != '\t') && (line[i] != '\n'))
            {
                charFlag = 1;
                // Set flag to 1 signifying that a non whitespace character was found
                
                tok = strtok(line, " \t\n");
                // Get the token for the potential label
                
                tokLength = (int)strlen(tok) - 1;
                // Get the last index of the token by subtracting 1 from the length.
                
                if isLabel(tok, tokLength)
                // Checks if the current token is a label by checking if the last character of token is a ':'
                {
                    tok = strtok(NULL, " \t\n");
                    // Get the next token
                }// End if isLabel
                
                if isPseudoOp(tok)
                // Checks if the current token is a pseudo opcode by checking if the first character of
                // token is a '.'.
                {
                    if isResw(tok)
                    // Checks if the token is ".resw"
                    {
                        tok = strtok(NULL, " \t\n");
                        // Get the next token which is the opperand
                        opNum = atoi(tok);
                        // Convert the opperand to an integer
                        lcVal += atoi(tok);
                        // Add the number to the lc value

                        immediate = opNum;
                        // Insert opNum into immediate
                        
                        lcVal = assembleResw(lcVal, immediate);
                        // Send to ".resw" function
                    }// End if isResw
                    
                    else if isWord(tok)
                    // Checks if the token is ".word"
                    {
                        op1 = strtok(NULL, " \t\n:");
                        // Get the next token which is the first opperand
                        opNum1 = atoi(op1);
                        // Convert the opperand to an integer
                        
                        op2 = strtok(NULL, " \t\n:");
                        // Get the noxt token which is the second opperand
                        opNum2 = atoi(op2);
                        // Convert the opperand to an integer
                        
                        lcVal += atoi(tok);
                        // Add the number to the lc value
                        
                        lcVal = assembleWord(lcVal, opNum1, opNum2);
                        // Send numbers to to ".word" function
                    }// End if isWord
                }// End if isPseudoOp
                
                else
                // Runs if the token is a normal opcode
                {
                    while opTable(x)
                    // Loops through the opcode table for each entry
                    {
                        if isOpcode(opCodeTable[x].mnemonic, tok)
                        // Checks if the current token is a valid opcode
                        {
                            invalidOpcodeFlag = 0;
                            // Set flag to 0 signifying a valid opcode was found
                            
                            if isFirstOperand(opCodeTable[x].numOps)
                            // Checks if there are more than 0 operands
                            {
                                op1 = strtok(NULL, " ,\t\n");
                                // Get the first operand
                                
                                if isRegister(op1[0])
                                // Checks if op1 is a register
                                {
                                    op1[0] = ' ';
                                    opNum1 = atoi(op1);
                                    targetReg = opNum1;
                                    // Insert opNum1 into target register
                                }
                                
                                else if isInParenthesis(op1[0])
                                // Checks if op1 is in parenthesis
                                {
                                    op1[0] = ' ';
                                    op1[((int)strlen(op1) - 1)] = ' ';
                                    opNum1 = atoi(op1);
                                }
                                
                                else if isImmediate(op1[0])
                                // Checks if op1 is a number
                                {
                                    opNum1 = atoi(op1);
                                }
                                
                                else
                                // Opperand is a label
                                {
                                    op1Flag = 1;
                                    //strcpy(label, op1);
                                    // Copy into label
                                    errorCodes.undefinedLabelFlag = findUndefinedLabel(op1);
                                    // Send tok to function findUndefined label to see if the label is defined
                                }
                                
                            }
                            
                            if isSecondOperand(opCodeTable[x].numOps)
                            // Checks if there are more than 1 operands
                            {
                                op2 = strtok(NULL, " (,\t\n");
                                // Get the second operand
                                
                                
                                if isRegister(op2[0])
                                // Checks if op2 is a register
                                {
                                    op2[0] = ' ';
                                    opNum2 = atoi(op2);
                                    sourceReg1 = opNum2;
                                    // Insert opNum into source register 1
                                }
                                
                                else if isInParenthesis(op2[0])
                                // Checks if op2 is in parenthesis
                                {
                                    op2[0] = ' ';
                                    op2[((int)strlen(op2) - 1)] = ' ';
                                    opNum2 = atoi(op2);
                                }
                                
                                else if isImmediate(op2[0])
                                // Checks if op2 is a number
                                {
                                    opNum2 = atoi(op2);
                                    immediate = opNum2;
                                }
                                
                                else
                                // Opperand is a label
                                {
                                    op2Flag = 1;
                                    //strcpy(label, op2);
                                    // Copy op2 in label
                                    errorCodes.undefinedLabelFlag = findUndefinedLabel(op2);
                                    // Send tok to function findUndefined label to see if the label is defined
                                }

                                
                                //opNum2 = atoi(op2);
                                // Convert second operand to an integer
                            }
                            
                            if isThirdOperand(opCodeTable[x].numOps)
                            // Checks if there are more than 2 operands
                            {
                                op3 = strtok(NULL, " ,\t\n");
                                // Get the third operand
                                
                                
                                if isRegister(op3[0])
                                // Checks if op3 is a register
                                {
                                    op3[0] = ' ';
                                    
                                    if (op3[((int)strlen(op3) - 1)] == ')')
                                    // Checks if register was in parenthesis meaning it is the first source register
                                    {
                                        op3[((int)strlen(op3) - 1)] = ' ';
                                        sourceReg1 = atoi(op3);
                                        // Insert into source register 1
                                    }
                                    
                                    else
                                    // Is the second source register
                                    {
                                        opNum3 = atoi(op3);
                                        sourceReg2 = atoi(op3);
                                        // Insert opNum into source register 2
                                    }
                                    
                                }
                                
                                else if isInParenthesis(op3[0])
                                // Checks if op3 is in parenthesis
                                {
                                    op3[0] = ' ';
                                    op3[((int)strlen(op3) - 1)] = ' ';
                                    opNum3 = atoi(op3);
                                }
                                
                                else if isImmediate(op3[0])
                                // Checks if op3 is a number
                                {
                                    opNum3 = atoi(op3);
                                    immediate = opNum3;
                                    // Insert opNum into shift amount
                                }
                                
                                else
                                // Opperand is a label
                                {
                                    op3Flag = 1;
                                    //strcpy(label, op3);
                                    // Copy op3 into label
                                    errorCodes.undefinedLabelFlag = findUndefinedLabel(op3);
                                    // Send tok to function findUndefined label to see if the label is defined
                                }
                            }
                            
                            if isTypeR(opCodeTable[x].format)
                            // Checks if current opcode is R format
                            {
                                assembleR(lcVal, opCodeTable[x].opcode, sourceReg1, sourceReg2, targetReg, immediate);
                                // Function call to assembleR
                            }
                            
                            else if isTypeI(opCodeTable[x].format)
                            // Checks if current opcode is I format
                            {
                                assembleI(lcVal, opCodeTable[x].opcode, sourceReg1, targetReg, immediate);
                                // Function call to assembleI
                            }
                            
                            else if isTypeJ(opCodeTable[x].format)
                            // Checks if current opcode is J format
                            {
                                if (op1Flag == 1)
                                {
                                    assembleJ(lcVal, opCodeTable[x].opcode, sourceReg1, targetReg, op1);
                                    // Function call to assembleJ
                                }
                                else if (op2Flag == 1)
                                {
                                    assembleJ(lcVal, opCodeTable[x].opcode, sourceReg1, targetReg, op2);
                                    // Function call to assembleJ
                                }
                                else if (op3Flag == 1)
                                {
                                    assembleJ(lcVal, opCodeTable[x].opcode, sourceReg1, targetReg, op3);
                                    // Function call to assembleJ
                                }
                            }
                            
                            op1Flag = 0;
                            op2Flag = 0;
                            op3Flag = 0;
                            
                            break;
                            // Break out of loop
                        }// End if isOPcode
                        
                        x++;
                        // Increment while loop counter
                    }// End while opTable
                    
                    x = 0;
                    // Reset opTable while loop counter
                    
                    if isInvalidOpcode(invalidOpcodeFlag)
                    // Checks if the current opcode is invalid and adds
                    {
                        errorCodes.invalidOpcodeFlag = 1;
                        insertIllegalOpcode(tok, lineNum);
                        // Call insertIllegalOpCode to insert into error file 
                    }
                    
                    lcVal += 1;
                    // Increment lcValue
                }// End else opcode
                
                break;
                // Break out of loop
            }// End if isValidChar
            
            i++;
        }// End while lineNotNull
        
        invalidOpcodeFlag = 1;
        // Reset invalid OpcodeFlag
        i = 0;
        // Reset counter to 0
        
        immediate = 0;
        sourceReg1 = 0;
        sourceReg2 = 0;
        targetReg = 0;
        // Reset register values for next instruction
    }// End while linesInAsmFile
    
    return errorCodes;
    // Return errorCodes struct with error codes
}

void errorHandler(FILE *asmFile, char *errName, int printIllegalOpcodes, int printUndefined, int printMultDefined)
{
    char line[LINE_SIZE];
    // Stores a line from the source file
    int i = 0;
    // Counter to loop through each "line" character array
    int charFlag;
    // Flag signifying whether or not the line had a non whitespace character
    int lineNum = 0;
    // Counter to store the number of lines with non whitespace characters
    FILE *errFile;
    // Used to reference the output error file
    
    if openErrFile(errFile, errName)
    // Open error file. If it doesn't open, print error message and close program.
    {
        fprintf(stderr, "Error: Error File Did Not Open\n");
        exit(1);
    }

    
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
                
                fprintf(errFile, "%d\t%s", lineNum, line);
                // Write error to error file

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
            fprintf(errFile, "%d%s", lineNum, "\n");
            
            i = 0;
            // Reset to 0 so character array starts at the beginning of the next line
        }
    }
    
    if illegalOpcodes(printIllegalOpcodes)
    // Checks if the illegalOpcodes flag is 1 signifying there is an illegal opcodes
    {
        fprintf(errFile, "\n\nIllegal Opcodes:\n");
        printIllegalOpcodeList(errFile);
    }
    
    if multDefinedLabel(printMultDefined)
        // Checks if the multDefinedLabelFlag is 1 signfying there are multiply defined labels
    {
        fprintf(errFile, "Multiply Defined Labels:\n");
        printMultDefinedLabelList(errFile);
    }

    
    if undefinedLabel(printUndefined)
    // Checks if the undefinedLabelFlag is 1 signifying there is an undefined label
    {
        fprintf(errFile, "\nUndefined Labels:\n");
        printUndefinedLabelList(errFile);
    }
    
    if closeErrFile(errFile)
    // Closes the error file and checks if it doesn't close
    {
        fprintf(stderr, "Error: Could Not Close Error File\n");
        exit(1);
    }
}


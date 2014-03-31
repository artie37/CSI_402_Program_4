// functions.c
// Arthur Knapp
// AK146316

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "externs.h"
#include "prototypes.h"
#include "macros.h"

void errorChecker()
{
    char line[LINE_SIZE];
    // Stores a line from the source file
    int i = 0;
    // Counter to loop through each "line" character array
    int charFlag;
    // Flag signifying whether the line had a non whitespace character or not
    int lineNum = 0;
    // Counter to store the number of lines with non whitespace characters in the file
    
    while linesInAsmFile(line, LINE_SIZE, asmFile)
    // Loops through the source file and stores each line in th character array "line".
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

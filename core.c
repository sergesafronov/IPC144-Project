#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("\n<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
int inputInt(void) {
    char newLine = 0;
    int integer;
    do {
        scanf("%d%c", &integer, &newLine);
        if (newLine == '\n') {
            return integer;
        }
        else {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (1);
}

int inputIntPositive(void) {
    do {
        int positive = inputInt();
        if (positive > 0) {
            return positive;
        }
        else {
            printf("ERROR! Value must be > 0: ");
        }
    } while (1);
}

int inputIntRange(int lowerBound, int upperBound) {
    do {
        int ranged = inputInt();
        if (ranged >= lowerBound && ranged <= upperBound) {
            return ranged;
        }
        else {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (1);
}

char inputCharOption(const char* allowedOptions) {
    char str[64];
    do {
        scanf(" %s", str);
        int i = 0;
        for (; i < strlen(allowedOptions); i++) {
            if (str[0] == allowedOptions[i] && strlen(str) == 1) {
                clearInputBuffer();
                return str[0];
            }
        }
        printf("ERROR: Character must be one of [%s]: ", allowedOptions);
        clearInputBuffer();
    } while (1);
}

void inputCString(char* result, int minChars, int maxChars) {
    int nChars = 0;
    char input[64];
    char format[8];
    sprintf(format, "%%%d[^\n]", maxChars + 1);
    do {
        scanf(format, input);
        clearInputBuffer();
        nChars = (int)strlen(input);
        if (minChars == maxChars) {
            if (nChars != minChars) {
                printf("Invalid 10-digit number! Number: ");
            }
            else {
                strncpy(result, input, maxChars + 1);
                return;
            }
            continue;
        }
        if (nChars < minChars) {
            printf("ERROR: String length must be between %d and %d chars: %s", minChars, maxChars, result);
            input[0] = '\0';
            continue;
        }
        if (nChars > maxChars) {
            printf("ERROR: String length must be no more than %d chars: %s", maxChars, result);
            input[0] = '\0';
            continue;
        }
        strncpy(result, input, maxChars + 1);

        return;
    } while (1);
}


void displayFormattedPhone(const char* phone) {
    if (!phone || strlen(phone) != 10) {
        printf("(___)___-____");
        return;
    }
    int i = 0;
    while (i < 10) {
        if (phone[i] < '0' || phone[i] > '9') {
            printf("(___)___-____");
            return;
        }
        i++;
    }
    printf("(%c%c%c)%c%c%c-%c%c%c%c",
        phone[0], phone[1], phone[2],
        phone[3], phone[4], phone[5],
        phone[6], phone[7], phone[8],
        phone[9]);
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////


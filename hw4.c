// Lex Albrandt
// albrandt@pdx.edu
// 05/12/25
// CS 350
// HW 4 final

// The purpose of this code is to demonstrate Horspool's Algorithm
// 
// NOTE: I set this up so that an input.txt could be read in with input redirection

// Includes
#include <stdio.h>
#include <string.h>

// Constants
#define ARRAY_SIZE 1000                                         // Array size for text and pattern
#define ALPHABET_SIZE 256                                       // Array size for ascii alphabet

// Prototypes
void create_shift_table(char *, int, int []);                   // Function to create the shift table
int horspools(char *, int *, int, int, char *);                 // Function for horspool's check

int main()
{
    char pattern[ARRAY_SIZE];                                   // Char array for pattern
    char text[ARRAY_SIZE];                                      // Char array for text
    int shift_table[ALPHABET_SIZE];                             // Char array for shift table
    char data = '\0';                                           // Data variable
    int pattern_size = 0;                                       // Pattern size variable
    int text_size = 0;                                          // Text size variable
    int result = 0;                                             // Variable to catch the result of horspools

    // read in pattern
    // fgets(array, size, stream)
    fgets(pattern, ARRAY_SIZE, stdin);
    pattern[strcspn(pattern, "\n")] = '\0';                     // sets null terminator

    // read in text
    fgets(text, ARRAY_SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';

    // debug for pattern/text read in
    printf("Pattern: %s\n", pattern);
    printf("Text: %s\n", text);

    pattern_size = strlen(pattern);
    text_size = strlen(text);

    // create the shift table
    create_shift_table(pattern, pattern_size, shift_table);
    
    result = horspools(text, shift_table, pattern_size, text_size, pattern);

    if (result == -1)
        printf("Pattern not found!");
    else
        printf("Pattern found at index: %d", result);
    
    printf("\n");

}


// Function to create the shift table
void create_shift_table(char pattern[], int pattern_size, int shift_table[])
{
    // initialize the shift table where every element is the length of the pattern
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        shift_table[i] = pattern_size;
    }

    for (int j = 0; j <= pattern_size - 2; ++j)
    {
        shift_table[pattern[j]] = pattern_size - 1 - j;
    }
}


// Function to perform horspool's algorithm
int horspools(char *text, int *shift_table, int pattern_size, int text_size, char *pattern)
{
    int i = pattern_size - 1;

    while (i < text_size)
    {
        int k = 0;

        while (k < pattern_size && pattern[pattern_size - 1 -k] == text[i - k])
        {
            ++k;
        }
        
        if (k == pattern_size)
            return (i - pattern_size + 1);

        i += shift_table[text[i]];
        
    }

    return -1;
}
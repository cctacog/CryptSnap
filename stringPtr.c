#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* stringPtr(char* code)
{
    int w = 0, x = 1;
    int m1;

    code = (char*)malloc(sizeof(char));

    printf("\nEnter string : ");

    while (m1 != '\n')
    {
        // read the input from keyboard standard input
        m1 = getc(stdin);

        // re-allocate (resize) memory for character read to be stored
        code = (char*)realloc(code, x * sizeof(char));

        // store read character by making pointer point to c
        code[w] = m1;

        w++;
        x++;
     }

    code[w-1] = '\0'; // at the end append null character to mark end of string

    return code;
}

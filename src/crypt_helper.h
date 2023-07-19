#ifndef CRYPT_HELPER
#define CRYPT_HELPER

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_ops.h"

/*
Sophia Garcia
01-31-2023
*/

//this is usng a macro to define and initialize any future new instances
enum Operator {AND, OR, NAND, NOR, XOR, XNOR, NONE} Operator;
typedef struct The_Round
{
    Stack stack;
    char code[100];
    char key[100];
    char secret[100];
    int code_len;
    int play_again;
} The_Round;

//the_round functions
void transfer(const The_Round terms_1, The_Round *terms_2);

//calculator functions
char possibleActions(enum Operator i, char c, char k);
char alphabet(int b);
char alphabet_print_listed(char alphabet[]);
char alphabet_print(char alphabet[], int letter);
#endif
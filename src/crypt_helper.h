#ifndef CRYPT_HELPER
#define CRYPT_HELPER

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
/*
Sophia Garcia
01-31-2023
*/

#define INIT_BINARY_FORM { 8 }
//this is usng a macro to define and initialize any future new instances
enum Operator {AND, OR, NAND, NOR, XOR, XNOR} Operator;
char possibleActions(enum Operator i, char c, char k);
char alphabet(int b);
char alphabet_print_listed(char alphabet[]);
char alphabet_print(char alphabet[], int letter);
#endif
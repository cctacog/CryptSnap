#ifndef CRYPT_HELPER
#define CRYPT_HELPER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum {AND, OR, NAND, NOR, XAND, XOR} Operator;

typedef struct Binary_Form
{
    int element[8];
    int slot;

    Binary_Form() 
    {
        slot = 8;
        
    }

    // int *get(int pos);
    // void *replace(int val);
    // void *replace(int val, int pos);
};

char possibleActions(Operator i, char c, char k);
char* stringPtr(char* code, char* type);
//char num_let(int i, char one, char two);
//no need bc either code of words or code of integers
char char_alphabet(int b);
int des(char num);
struct Binary_Form ascii_to_bin(int letter, struct Binary_Form binary_c);
struct Binary_Form xand_operate(struct Binary_Form one, struct Binary_Form two);
int xand_each(int c1, int c2);
int bin_to_ascii(struct Binary_Form rev);

#endif
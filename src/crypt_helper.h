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

enum Operator {AND, OR, NAND, NOR, XAND, XOR} Operator;

typedef struct Binary_Form
{
    int element[8];
    int slot;
}Binary_Form;

char possibleActions(enum Operator i, char c, char k);
//char* stringPtr(char* code, char* type);
//only used when malloc really needed not really tha case here
//char num_let(int i, char one, char two);
//no need bc either code of words or code of integers
char alphabet(int b);
//int des(char num);
//no need treating all as characters
int get_O(int pos, struct Binary_Form* this_Binary);
void replace(int val, struct Binary_Form* this_Binary);
void replace_pos(int val, int pos, struct Binary_Form* this_Binary);
struct Binary_Form ascii_to_bin(int letter, struct Binary_Form* binary_c);
struct Binary_Form xand_operate(struct Binary_Form one, struct Binary_Form two);
int xand_each(int c1, int c2);
int bin_to_ascii(struct Binary_Form rev);

#endif
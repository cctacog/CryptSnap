#ifndef CRYPT_HELPER
#define CRYPT_HELPER

#include "the_round.h"

/*
Sophia Garcia
01-31-2023
*/

//calculator functions
//void code_thru_queue(The_Round *terms);
void code_thru_array(The_Round *terms);
void code_thru_stack(The_Round *terms);
char* print_op(const enum Operator op);
unsigned char possibleActions(enum Operator i, unsigned char c, unsigned char k);
char alphabet(int b);
char alphabet_print_listed(char alphabet[]);
char alphabet_print(char alphabet[], int letter);

#endif
#ifndef CRYPT_HELPER
#define CRYPT_HELPER

#include "the_round.h"

/*
Sophia Garcia
01-31-2023
*/

//calculator functions
//void code_thru_queue(The_Round *terms);
void code_thru_queue(The_Round *terms);
void code_thru_stack(The_Round *terms);
char* print_op(const enum Operator op);
void str_to_array(char *arr1, uint16_t hex1);
void str_trandsform(char *arr1, char *arr2);
uint16_t possibleActions(enum Operator i, uint16_t h1, uint16_t h2);
char alphabet(int b);
char alphabet_print_listed(char alphabet[]);
char alphabet_print(char alphabet[], int letter);

#endif
#ifndef CRYPT_HELPER
#define CRYPT_HELPER

#include "reference.h"
#include "the_round.h"
#include "stack_ops.h"
#include "queue_ops.h"

/*
Sophia Garcia
01-31-2023
*/

//calculator functions
char possibleActions(enum Operator i, char c, char k);
char alphabet(int b);
char alphabet_print_listed(char alphabet[]);
char alphabet_print(char alphabet[], int letter);
#endif
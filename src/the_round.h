#ifndef THE_ROUND
#define THE_ROUND

#include "reference.h"
#include "crypt_helper.h"

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


#endif
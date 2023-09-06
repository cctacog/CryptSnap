#ifndef THE_ROUND
#define THE_ROUND

#include "stack_ops.h"
#include "queue_ops.h"

typedef struct The_Round
{
    Stack stack;
    Queue queue;
    char code[100];
    char key[100];
    char secret[100];
    int code_len;
    int play_again;
} The_Round;

//the_round functions
void transfer(const The_Round terms_1, The_Round *terms_2);
void empty_q(The_Round *terms_);
void empty_s(The_Round *terms_);
#endif
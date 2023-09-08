#ifndef THE_ROUND
#define THE_ROUND

#include "stack_ops.h"
#include "queue_ops.h"
#include "tables.h"

#define BOUND_X 28
#define BOUND_Y 30

typedef struct The_Round
{
    Stack stack;
    Queue queue;
    unsigned char code[100];
    unsigned char key[100];
    //char secret[100];
    int code_len;
    int play_again;
    char background[BOUND_Y][BOUND_X];    
    Table gate_s[6];    
    Table problem;
    char words[75];
    char table[BOUND_Y - 26];    
} The_Round;

//the_round functions
void intro(The_Round *user);
void fill_Tables(The_Round *user);
void transfer(const The_Round user_1, The_Round *user_2);
void empty_q(The_Round *user_);
void empty_s(The_Round *user_);
void printer(const The_Round *user);
#endif
#ifndef THE_ROUND
#define THE_ROUND

#include "stack_ops.h"
#include "queue_ops.h"
#include "tables.h"

#define BOUND_X 56
#define BOUND_Y 20

typedef struct The_Round
{
    Stack stack;    
    enum Operator ops_order[10];
    unsigned char code[10];
    unsigned char key[10];
    unsigned char secret[10];
    int code_len;
    int play_again;
    char background[BOUND_Y][BOUND_X];    
    Table gate_s[6];    
    Table problem;       
} The_Round;

//the_round functions
void intro(The_Round *user);
void level_one(The_Round *user);
void level_two(The_Round *user);
void level_three(The_Round *user);
void clear_backgrd(The_Round *user);
void initialize_gateTables(The_Round *user);
void enter_words(The_Round *user, char *phrase);
void transfer(const The_Round user_1, The_Round *user_2);
void empty_s(The_Round *user_);
void printer_background(const The_Round *user);
void implement_aTable(The_Round *user, const Table *table, int row, int column);
#endif
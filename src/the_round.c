#include "the_round.h"

void intro(The_Round *user)
{
    fill(user);

    
}

void fill(The_Round *user)
{
    user->table[0] = ' ';
    user->table[1] = '_';
    user->table[2] = '|';
    user->table[3] = '\n';  

    for(int i = 0; i < BOUND_Y; ++i)
    {
        for(int j = 0; j < BOUND_X; ++j)
        {
            if(i == 0)
            {
                user->background[i][j] = user->table[1];
            }
            else if(j == 0 || j == BOUND_X - 2)
            {
                user->background[i][j] = user->table[2];
            }
            else if(j == BOUND_X - 1)
            {
                user->background[i][j] = user->table[3];
            }
            else
            {
                user->background[i][j] = user->table[0];
            }
        }
    }      
}

void transfer(const The_Round terms_1, The_Round *terms_2)
{
    terms_2->code_len = terms_1.code_len;
    for(int i = 0; i < terms_1.code_len; ++i)
    {
        terms_2->code[i] = terms_1.code[i];
    }
    for(int i = 0; i < 20 && terms_1.key[i-1] != '\0'; ++i)
    {
        terms_2->key[i] = terms_1.key[i];
    }
}

void empty_q(The_Round *terms_)
{
    for(int i = terms_->queue.item_Count; i > 0; --i)
    {        
        remove_q(&(terms_->queue));
    }
}
void empty_s(The_Round *terms_)
{
    for(int i = 0; i < MAX && isEmpty_s(&(terms_->stack)) == 1; ++i)
    {
        pop(&(terms_->stack));
    }    
}

void printer(const The_Round *user)
{
    for(int i = 0; i < BOUND_Y; ++i)
    {
        for(int j = 0; j < BOUND_X; ++j)
        {
            printf("%c", user->background[i][j]);
        }
    }
}

void printer(const Table *table)
{
    for(int i = 0; i < table->length; ++i)
    {
        for(int j = 0; j < table->width; ++j)
        {
            if(i % 2 == 0 && j % 2 == 0)
            {
                
            }
        }
    }
}

void initialize_table(Table *table, char *filler, int len, int width)
{
    table->length = len;
    table->width = width;    
    int count = 0;
    while(*filler != '\0')
    {
        table->filler[count] = *filler;
        ++filler;
    }
}
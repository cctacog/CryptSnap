#include "the_round.h"
#include "crypt_helper.h"

void intro(The_Round *user)
{
    fill(user);

    
}

void initialize_gateTables(The_Round *user)
{
    int gate_count = 0;
    char filler[15];
    while(gate_count < 6)
    {
        
        filler[0] = 'x';
        filler[1] = 'y';
        filler[2] = 'z';
        for(int i = 0; i < 2; ++i)
        {
            filler[3+i] = i;
            for(int j = 0; j < 2; ++j)
            {
                filler[4+j] = j;
                filler[5+j] = possibleActions(gate_count + 1, i, j);
            }
        }
        initialize_table(&user->gate_s[gate_count + 1], &filler, 11, 7);
    }
}

void fill(The_Round *user)
{

    for(int i = 0; i < BOUND_Y; ++i)
    {
        for(int j = 0; j < BOUND_X; ++j)
        {
            if(i == 0)
            {
                user->background[i][j] = '_';
            }
            else if(j == 0 || j == BOUND_X - 2)
            {
                user->background[i][j] = '|';
            }
            else if(j == BOUND_X - 1)
            {
                user->background[i][j] = '\n';
            }
            else
            {
                user->background[i][j] = ' ';
            }
        }
    }      
}

void enter_words(The_Round *user, char *phrase)
{
    for(int i = 2; i < 5 && *phrase != '\0'; ++i)
    {
        int j = 3;
        while(user->background[i][j] + 1 != '|')
        {
            user->background[i][j] = *phrase;
            ++phrase;
            ++j;
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

void printer_background(const The_Round *user)
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
    int count = 0;
    for(int i = 0; i < table->length; ++i)
    {
        for(int j = 0; j < table->width; ++j)
        {
            if(i == 0 || i == table->length - 1)
            {
                printf("_");
            }
            else if(i % 2 == 0 && j % 2 == 0)
            {
                printf(" ");
            }
            else if(i % 2 == 0)
            {
                printf("_");
            }
            else if(j % 2 == 0)
            {
                printf("|");
            }
            else
            {
                printf("%c", table->filler[count]);
            }
        }
        ++count;
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
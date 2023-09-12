#include "the_round.h"
#include "crypt_helper.h"

void intro(The_Round *user)
{
    clear_backgrd(user);
    initialize_gateTables(user);    
    char intro[75] = "Welcome to your introduction to Logic gates and LFSR's!";    
    enter_words(user, intro);      
    user->code[0] = 1;
    user->code[1] = 1;           
    user->code[2] = 0;
    user->key[0] = 1;
    user->key[1] = 0;
    user->key[2] = 1;

    initialize_table(&(user->problem), "110101   ", 7, 7);    
    printer_background(user);      
    char next_up[75] = "Now you need to start from the beginning...LOGIC GATES!";
    enter_words(user, next_up);
    printer_background(user);
}

void level_one(The_Round *user)
{
    enum Operator op = AND;
    while(op != NONE)
    {   
        clear_backgrd(user);
        implement_aTable(user, &(user->problem), 6, 11);
        implement_aTable(user, &(user->gate_s[0]),9, 5);
        char into_lvl[75] = "Now let us try and solve for an operation with the below bits!:";
        enter_words(user, into_lvl);
        printer_background(user);
        insert(&(user->queue), op);
        code_thru_queue(user);
        printf("What do you think the result will be for %s?: ", print_op(op));
        char answ[10];
        gets(answ);    
        for(int i = 0; i < 10; ++i)
        {            
            switch(answ[i])
            {
                case '1':
                    answ[i] = 1;                
                    break;
                case '0':
                    answ[i] = 0;
                    break;
                default:
                    answ[i] = '-';        
            }
        }          
        if(answ[0] == user->secret[0] && answ[1] == user->secret[1] && answ[2] == user->secret[2]) 
        {        
            enter_words(user, "You got it!");        
        }
        else enter_words(user, "Boo you failed");   
        printer_background(user);
        ++op; 
    }
}

void level_two(The_Round *user)
{
    //user practices trhee problems where the code undergoes two gates
    //user then see's a three gate problem for encrypting and decrypting    
}

void level_three(The_Round *user)
{
    //user introduced to LFSR's and set to 5 practice problems
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
        initialize_table(&user->gate_s[gate_count + 1], filler, 11, 7);
        ++gate_count;
    }
}

void clear_backgrd(The_Round *user)
{
    for(int i = 0; i < BOUND_Y; ++i)
    {
        for(int j = 0; j < BOUND_X; ++j)
        {
            if(j == BOUND_X - 1)
            {
                user->background[i][j] = '\n';
            }
            else if(i == 0 || i == BOUND_Y - 1)
            {
                user->background[i][j] = '_';
            }
            else if(j == 0 || j == BOUND_X - 2)
            {
                user->background[i][j] = '|';
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
    for(int i = 2; i < 5; ++i)
    {
        int j = 3;
        while(user->background[i][j+1] != '|')
        {
            user->background[i][j] = ' ';                        
            ++j;
        }
    }
    for(int i = 2; i < 5 && *phrase != '\0'; ++i)
    {
        int j = 3;
        while(user->background[i][j+1] != '|' && *phrase != '\0')
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
    Sleep(2500);
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
        ++count;
    }
}

void implement_aTable(The_Round *user, const Table *table, int row, int column)
{
    int count = 0;
    if(row < 0 || row >= BOUND_Y || row+(table->length) >= BOUND_Y)
        return;
    else if(column < 0 || row >= BOUND_X || column+(table->width) >= BOUND_X)
        return;
    user->background[row][column] = ' ';
    for(int i = 0; i < table->length; ++i)
    {
        int col = column;
        for(int j = 0; j < table->width; ++j)
        {            
            if(i == 0 || i == table->length - 1)
            {
                user->background[row][col] = '_';
            }
            else if(i % 2 == 0 && j % 2 == 0)
            {
                user->background[row][col] = ' ';
            }
            else if(i % 2 == 0)
            {
                user->background[row][col] = '_';
            }
            else if(j % 2 == 0)
            {
                user->background[row][col] = '|';
            }
            else
            {
                if(table->filler[count] != '\0')
                {                        
                    user->background[row][col] = table->filler[count];
                    ++count;
                }
                else 
                {
                    user->background[row][col] = ' ';
                }
                
            }
            ++col;                        
        }
        ++row;
        
    }
}
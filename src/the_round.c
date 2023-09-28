#include "the_round.h"
#include "crypt_helper.h"

void intro(The_Round *user)
{
    clear_backgrd(user);
    def_values_s(&(user->stack));
    def_values_q(&(user->queue));
    initialize_gateTables(user);    
    char intro[75] = "Welcome to your introduction to Logic gates and LFSR's!";    
    enter_words(user, intro);     
    user->code_hex = 0x08u;
    user->key_hex = 0x0Au; 
    user->code_len = 4;
    initialize_table(&(user->problem), "10001010    ", 7, 9);           
    char next_up[75] = "Now you need to start from the beginning...LOGIC GATES!";
    enter_words(user, next_up);    
    printf("code: %x\n", (user->code_hex));    
}

void level_one(The_Round *user)
{
    enum Operator op = AND;        
    while(op <= XNOR)
    {           
        implement_aTable(user, &(user->problem), 6, 11);
        implement_aTable(user, &(user->gate_s[op]), 6, 2);      
        char into_lvl[75] = "Now let us try and solve the below bits!:";
        enter_words(user, into_lvl);          
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
        char *str_answ = "Yay you got it!";  
        int two_ = 8;  
        printf("%x\n", (user->secret_hex));
        for(int i = 3; i >= 0; --i)
        {            
            if(answ[i] != ((user->secret_hex >> i) & 1u));
            {
                str_answ = "Boo you failed";
                i = -1;
            }     
            two_/= 2;                   
        
        }                   
        enter_words(user, str_answ);        
        ++op; 
        free(str_answ);
    }    
}

void level_two(The_Round *user)
{
    //user practices thee problems where the code undergoes two gates
    //user then see's a three gate problem for encrypting and decrypting 
   // printf("cooki\n");    
    enum Operator ops[7] = {NAND, NOR, AND, OR, XNOR, XOR, NONE};      
    enter_words(user, "Here you will be working with two gates");   
    enter_words(user, "The code wil run through one gate with the key as before!");         
    enter_words(user, "Then the output will run through a second gate with the same key!");      
    int op = 0;
    while(op < 7 && ops[op] != NONE)
    {   
        enter_words(user, "Now let us try and solve the below bits!:");
        implement_aTable(user, &(user->problem), 6, 20);        
        implement_aTable(user, &(user->gate_s[ops[op]]), 6, 2);        
        implement_aTable(user, &(user->gate_s[ops[op + 1]]), 6, 10);   
        printer_background(user);                            
        insert(&(user->queue), ops[op]);
        insert(&(user->queue), ops[op + 1]);
        code_thru_queue(user);          
        printf("What do you think the result will be for %s and %s?: ", print_op(ops[op]), print_op(ops[op+1]));                                
        char answ1[10];
        gets(answ1);    
        for(int i = 0; i < 10; ++i)
        {            
            switch(answ1[i])
            {
                case '1':
                    answ1[i] = 1;                
                    break;
                case '0':
                    answ1[i] = 0;
                    break;
                default:
                    answ1[i] = '-';        
            }
        }          
        char *str_answ1 = "Yay you got it!";        
        for(int i = 3; i >= 0; --i)
        {
            if(answ1[i] != ((user->secret_hex >> i) & 1u))
            {
                str_answ1 = "Boo you failed";
                i = 4;
            }
        
        }           
        enter_words(user, str_answ1);          
        op += 2;
    }   
    clear_backgrd(user); 
    enter_words(user, "This output will run through a three gates with the same key!"); 
    
    enter_words(user, "Now let us try and solve the below bits!:");  
    implement_aTable(user, &(user->problem), 6, 26);        
    implement_aTable(user, &(user->gate_s[AND]), 6, 2);        
    implement_aTable(user, &(user->gate_s[OR]), 6, 10);
    implement_aTable(user, &(user->gate_s[NAND]), 6, 18);                 
    printer_background(user);
    insert(&(user->queue), AND);
    push(&(user->stack), AND);
    insert(&(user->queue), OR);
    push(&(user->stack), OR);
    insert(&(user->queue), NAND);
    push(&(user->stack), NAND);      
    code_thru_queue(user);        
    printf("What do you think the result will be for %s, %s and %s?: ", print_op(AND), print_op(OR), print_op(NAND));                                
    char answ2[10];
    gets(answ2);    
    for(int i = 0; i < 10; ++i)
    {            
        switch(answ2[i])
        {
            case '1':
                answ2[i] = 1;                
                break;
            case '0':
                answ2[i] = 0;
                break;
            default:
                answ2[i] = '-';        
        }
    }          
    char *str_answ2 = "Yay you got it!";        
    for(int i = 3; i >= 0; --i)
    {
        if(answ2[i] != ((user->secret_hex >> i) & 1u))
        {
            str_answ2 = "Boo you failed";
            i = 4;
        }
    
    }       
    enter_words(user, str_answ2);   
    implement_aTable(user, &(user->problem), 6, 26);        
    implement_aTable(user, &(user->gate_s[AND]), 6, 2);        
    implement_aTable(user, &(user->gate_s[OR]), 6, 10);
    implement_aTable(user, &(user->gate_s[NAND]), 6, 18);   
    printer_background(user);  
    printf("What do you think the result will if you reversed the gate order and encrypted the secret with the key?: "); 
    code_thru_stack(user);                               
    char answ3[10];
    gets(answ3);    
    for(int i = 0; i < 10; ++i)
    {            
        switch(answ3[i])
        {
            case '1':
                answ3[i] = 1;                
                break;
            case '0':
                answ3[i] = 0;
                break;
            default:
                answ3[i] = '-';        
        }
    }          
    char *str_answ3= "Yay you got it!";        
    for(int i = 3; i >= 0; --i)
    {
        if(answ2[i] != ((user->secret_hex >> i) & 1u))
        {
            str_answ3 = "Boo you failed";
            i = 4;
        }
    
    }       
    enter_words(user, str_answ3);       
}

void level_three(The_Round *user)
{
    //user introduced to LFSR's and set to 5 practice problems
    enter_words(user, "Have you heard of the Fibonacci Sequence?");
    enter_words(user, "Well what if I told you there was the Fibonacci Encryption?");
    enter_words(user, "This encryption deals with Linear Feedback Shift Registar encryption! Or as some might say LFSR encryption");
    enter_words(user, "Here LFSR encryption will be dealing with the XOR and XNOR gates we practiced earlier!");
    enter_words(user, "This will also include stacking one gate over another based on a previous gate input!");        
    enter_words(user, "For our 4 bit set example, we will be XORing our first bit with our third bit");
    enter_words(user, "And the then the fourth with our result!");
    enter_words(user, "What do you think this will be?");
    implement_aTable(user, &(user->gate_s[XOR]), 2, 7);
    implement_aTable(user, &(user->problem), 6, 26); 
    
}

void initialize_gateTables(The_Round *user)
{
    enum Operator gate_count = AND;
    //HARDCODED :)
    initialize_table(&user->gate_s[AND], "xyz000010100111", 11, 7);
    initialize_table(&user->gate_s[OR], "xyz000011101111", 11, 7);
    initialize_table(&user->gate_s[NAND], "xyz001011101110", 11, 7);
    initialize_table(&user->gate_s[NOR], "xyz001010100110", 11, 7);
    initialize_table(&user->gate_s[XOR], "xyz000011101110", 11, 7);
    initialize_table(&user->gate_s[XNOR], "xyz001010100111", 11, 7);
    /*
    make corrections because the gate inputs and outputs do not align with that of
    the specified gate lol im not really with it rn imma just focus in the levels
    then make it pretty laterrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
    :) 
    */
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
    clear_backgrd(user);
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
    printer_background(user);
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
    Sleep(1500);
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
    // if(row < 0 || row >= BOUND_Y || row+(table->length) >= BOUND_Y)
    //     return;
    // else if(column < 0 || row >= BOUND_X || column+(table->width) >= BOUND_X)
    //     return;
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
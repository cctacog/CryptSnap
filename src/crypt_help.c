#include "crypt_helper.h"
/*
Sophia Garcia
01-31-2023
*/


void code_thru_queue(The_Round *terms)
{
    for(int q = 0; !isEmpty_q(&(terms->queue)) && q < 10; ++q)
    {            
        printf("queue go!\n");             
        enum Operator op = remove_q(&(terms->queue)); 
        if(!q)
            terms->secret_hex = possibleActions(op, terms->code_hex, terms->key_hex);
        else 
            terms->secret_hex = possibleActions(op, terms->secret_hex, terms->key_hex);
    }
    for(int i = 3; i >= 0; --i)
    {
        printf("secret: %i\n", (terms->secret_hex >> i) & 1u);
    }
}

void code_thru_stack(The_Round *terms)
{   
    for(int s = 0; !isEmpty_s(&(terms->stack)); ++s)
    {
        enum Operator op = pop(&(terms->stack));     
        terms->secret_hex = possibleActions(op, terms->secret_hex, terms->key_hex);
    }
}

char* print_op(const enum Operator op)
{
    char *result;
    switch(op)
        {
            case AND:
                result = "AND";
                break;
            case OR:
                result = "OR";
                break;
            case NAND:
                result = "NAND";
                break;
            case NOR:
                result = "NOR";
                break;
            case XOR:
                result = "XOR";
                break;
            case XNOR:
                result = "XNOR";
                break;
            case NONE:
                result = "NONE";
                break;
            default:
                result = "nope";            
                break;
        }
     return result;
}


uint16_t possibleActions(enum Operator i, uint16_t h1, uint16_t h2)
{    
    uint16_t answ = 0;    
    switch(i)
    {
        case AND:
            answ = h1 & h2;
            break;
        case OR:
            answ = h1 | h2;
            break;
        case NAND:
            answ = ~(h1 & h2);
            break;
        case NOR:
            answ = ~(h1 | h2);
            break;
        case XOR:
            answ = h1 ^ h2;
            break;
        case XNOR:
            answ = ~(h1 ^ h2);
            break;
        case NONE:
            printf("oops\n");
            break;
        default:
            perror("Error by input\n");
            answ = 'f';
            break;
    }

    //answ &= 1u;
    printf("%x\n", answ);
    return answ;
}


char alphabet(int b)
{
    char alphabet[255];

    for(int i = 0; i < 255; i++)
    {
        alphabet[i] = i;
    }

    if(b >= 0)
    {
        return alphabet_print(alphabet, b);            
    }
    else
    {
        return alphabet_print_listed(alphabet);        
    }        
}

char alphabet_print_listed(char alphabet_[])
{
    char yn[10];
    printf("\n\nWould you like to see the C ascii alphabet?: [ex: yes] ");
    gets(yn);

    if(yn[0] == 'y' || yn[0] == 'Y')
        alphabet(-1);

    printf("\nHave a nice day!\n");
    const char non_printable[33][5] = {"NULL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", 
    "BEL", "BS", "TAB", "LF", "VT", "FF", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", 
    "NAK", "SYN", "CAN", "EM", "SUB", "ESC", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE" };
    char move;
    for(int i = 0; i < 255; i++)
    {
        printf("Ascii character of %i: ", i);
        if(i < 33)
        {
            printf(non_printable[i]);
        }
        else
        {
            printf("%c", alphabet_[i]);
        }
        if((i+1) % 2 == 0)
            move = '\n';
        else move = '\t';
        printf("%c", move);
    }       
    return move;
}

char alphabet_print(char alphabet[], int letter)
{
    return alphabet[letter];    
}

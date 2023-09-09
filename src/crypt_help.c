#include "crypt_helper.h"
/*
Sophia Garcia
01-31-2023
*/

void code_thru_queue(The_Round *terms)
{
    int iK = 0;
        
    for(int q = 0; isEmpty_q(&(terms->queue)) == 0; ++q)
    {        
        enum Operator op = remove_q(&(terms->queue));        
        //print_op(op);
        for(int i = 0; (i < terms->code_len) && (terms->code[i] != '\0'); ++i)
        {
            /*
            because a character cannot xor itself the
            array location will equal the said character
            */
            if(terms->code[i] == terms->key[iK] && (op == XOR || op == XNOR))
            {                
                continue;
            }

            char s;
            s = possibleActions(op, terms->code[i], terms->key[iK]);

            terms->code[i] = s;
            printf("\n%i", terms->code[i]);
            /*
            if terms->code about to end at the i+1 location
            then the code will end at i+1
            */
            iK++;

            if(terms->code[i+1] == '\0')
                terms->code[i+1] = '\0';
            if(terms->key[iK] == '\0')
                iK = 0;
        }
    }
}

void code_thru_stack(The_Round *terms)
{
    int iK = 0;
    for(int s = 0; isEmpty_s(&(terms->stack)) == 0; ++s)
    {
        enum Operator op = pop(&(terms->stack));     
        //print_op(op);   
        for(int i = 0; (i < terms->code_len) && (terms->code[i] != '\0') && op != NONE; ++i)
        {
            
            /*
            because a character cannot xor itself the
            array location will equal the said character
            */
            if(terms->code[i] == terms->key[iK] && (op == XOR || op == XNOR))
            {                
                continue;
            }

            unsigned char s;
            s = possibleActions(op, terms->code[i], terms->key[iK]);

            terms->code[i] = s;
            printf("\n%i", terms->code[i]);
            /*
            if terms->code about to end at the i+1 location
            then the code will end at i+1
            */
            iK++;
            
            if(terms->key[iK] == '\0')
                iK = 0;
        }
    }
}

void assign_op(enum Operator *op, const char operate, The_Round *terms)
{
    *op = (operate - '0' > 0 && operate - '0' < 7) ? operate - '0' : 0;
    insert(&(terms->queue), *op);
    push(&(terms->stack), *op);    
}
void print_op(const enum Operator op)
{
    switch(op)
        {
            case AND:
                printf("operator: AND\n");
                break;
            case OR:
                printf("operator: OR\n");
                break;
            case NAND:
                printf("operator: NAND\n");
                break;
            case NOR:
                printf("operator: NOR\n");
                break;
            case XOR:
                printf("operator: XOR\n");
                break;
            case XNOR:
                printf("operator: XNOR\n");
                break;
            case NONE:
                printf("oops\n");
                break;
            default:
                perror("NONE FOUND");            
                break;
        }
}

unsigned char possibleActions(enum Operator i, unsigned char c, unsigned char k)
{    
    int answ = 0;
    switch(i)
    {
        case AND:
            answ = c & k;
            break;
        case OR:
            answ = c | k;
            break;
        case NAND:
            answ = ~(c & k);
            break;
        case NOR:
            answ = ~(c | k);
            break;
        case XOR:
            answ = c ^ k;
            break;
        case XNOR:
            answ = ~(c ^ k);
            break;
        case NONE:
            printf("oops\n");
            break;
        default:
            perror("Error by input");
            answ = 'f';
            break;
    }
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

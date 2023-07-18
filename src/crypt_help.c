#include "crypt_helper.h"
/*
Sophia Garcia
01-31-2023
*/

char possibleActions(enum Operator i, char c, char k)
{
    int answ;
    switch(i)
    {
        case AND:
            answ = c & k;
            break;
        case OR:
            answ = c + k;
            break;
        case NAND:
            answ = ~(c & k);
            break;
        case NOR:
            answ = ~(c + k);
            break;
        case XOR:
            answ = c ^ k;
            break;
        case XNOR:
            answ = ~(c ^ k);
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

char alphabet_print_listed(char alphabet[])
{
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
            printf("%c", alphabet[i]);
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
    if(letter > 13 )
    {
        return alphabet[letter];
    }
}

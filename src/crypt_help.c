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
            answ = !(c ^ k);
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

    switch(b)
    {
    case -1:
        for(int i = 0; i < 255; i++)
        {
            printf("Ascii character of %i is: ", i);
            switch(i)
            {
                case 0:
                    printf("NULL");
                    break;
                case 7:
                    printf("BEL");
                    break;
                case 8:
                    printf("BS");
                    break;
                case 9:
                    printf("HT");
                    break;
                case 10:
                    printf("LF");
                    break;
                case 13:
                    printf("CR");
                    break;
                case 32:
                    printf("SPACE");
                    break;
                default:
                    printf("%c", alphabet[i]);
                    break;
            }
            if(((i+1) % 2 == 0))
            printf("\n");
            else printf("\t");
        }
        break;
    default:
        if(b < 0)
        {
            printf("\n((:%i))\n", b);
            int end = 256;
            b -= end;
            printf("\n((:%i))\n", b);
        }
        switch(b)
        {
        case 0:
            printf("[NULL]");
            break;
        case 7:
            printf("[BEL]");
            break;
        case 8:
            printf("[BS]");
            break;
        case 9:
            printf("[HT]");
            break;
        case 10:
            printf("[LF]");
            break;
        case 13:
            printf("[CR]");
            break;
        case 32:
            printf("[SPACE]");
            break;
        default:
            return alphabet[b];
            break;
        }
    }
    return '\n';

}

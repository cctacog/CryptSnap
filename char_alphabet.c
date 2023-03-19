#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Sophia Garcia
CISC 211
02-01-2023
*/

char char_alphabet(int b)
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
            char end = 256;
            b -= end;
            printf("\n((:%i))\n", b);
        }
        switch(b)
        {
        case 0:
            printf("[NULL");
            break;
        case 7:
            printf("[BEL");
            break;
        case 8:
            printf("[BS");
            break;
        case 9:
            printf("[HT");
            break;
        case 10:
            printf("[LF");
            break;
        case 13:
            printf("[CR");
            break;
        case 32:
            printf("[SPACE");
            break;
        default:
            return alphabet[b];
            break;
        }
    }
    return ']';

}

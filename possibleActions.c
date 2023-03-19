#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int possibleActions(int i, char c, char k)
{
    int answ;
    switch(i)
    {
    case 0:
        answ = c & k;
        break;
    case 1:
        answ = c + k;
        break;
    case 2:
        answ = ~(c & k);
        return answ;
        break;
    case 3:
        answ = ~(c + k);
        break;
    case 4:
        answ = c ^ k;
        break;
    default:
        printf("\nfuck this shit im out\n");
        answ = 'f';
        break;
    }
    return answ;
}

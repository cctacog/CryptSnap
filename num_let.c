#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Sophia Garcia
CISC 211
01-31-2023
*/

int possibleActions(int i, char c, char k);

int des(char num)
{
    int numb;
    char choice[20];
    printf("\nWould you like to treat %c as\na digit or a character?: ", num);
    gets(choice);
        if(choice[0] == 'd' || choice[0]== 'D')
            numb = num - 48;
        else numb = -1;
    return numb;
}

char num_let(int i, char one, char two)
{
    int codeNum = -1;
    int keyNum = -1;
    /*
        ask user if they would like the number to
        be interpreted as a digit or character 0-9
    */
    if((two < 58 && two > 47))
    {
        keyNum = des(two);
    }
    if((one < 58 && one > 47))
    {
        codeNum = des(one);
    }

    int secret;

    if(codeNum != -1 && keyNum != -1)
        secret = possibleActions(i, codeNum, keyNum);
    else if(codeNum != -1)
        secret = possibleActions(i, codeNum, two);
    else if(keyNum != -1)
        secret = possibleActions(i, one, keyNum);
    else secret = possibleActions(i, one, two);

    return secret;
}

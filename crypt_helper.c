#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Sophia Garcia
01-31-2023
*/

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


char* stringPtr(char* code)
{
    int w = 0, x = 1;
    int m1;

    code = (char*)malloc(sizeof(char));

    printf("\nEnter string : ");

    while (m1 != '\n')
    {
        // read the input from keyboard standard input
        m1 = getc(stdin);

        // re-allocate (resize) memory for character read to be stored
        code = (char*)realloc(code, x * sizeof(char));

        // store read character by making pointer point to c
        code[w] = m1;

        w++;
        x++;
     }

    code[w-1] = '\0'; // at the end append null character to mark end of string

    return code;
}


char possibleActions(int i, char c, char k)
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

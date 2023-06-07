#include "crypt_helper.h"
/*
Sophia Garcia
01-31-2023
*/

int des(char num)
{
    int numb;
    char choice[20];
    printf("\nWould you like to treat %c as\na digit or a character?: ", num);
    gets_s(choice);
        if(choice[0] == 'd' || choice[0]== 'D')
            numb = num - 48;
        else numb = -1;
    return numb;
}

// char num_let(int i, char one, char two)
// {
//     int codeNum = -1;
//     int keyNum = -1;
//     /*
//         ask user if they would like the number to
//         be interpreted as a digit or character 0-9
//     */
//     if((two < 58 && two > 47))
//     {
//         keyNum = des(two);
//     }
//     if((one < 58 && one > 47))
//     {
//         codeNum = des(one);
//     }

//     int secret;

//     if(codeNum != -1 && keyNum != -1)
//         secret = possibleActions(i, codeNum, keyNum);
//     else if(codeNum != -1)
//         secret = possibleActions(i, codeNum, two);
//     else if(keyNum != -1)
//         secret = possibleActions(i, one, keyNum);
//     else secret = possibleActions(i, one, two);

//     return secret;
// }


char* stringPtr(char* code, char* type)
{
    int w = 0, x = 1;
    int m1;

    code = (char*)malloc(sizeof(char));

    printf("\nEnter %s: ", type);

    while (m1 != EOF)
    {
        // read the input from keyboard standard input
        m1 = getchar();

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


char possibleActions(Operator i, char c, char k)
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
        return answ;
        break;
    case NOR:
        answ = ~(c + k);
        break;
    case XAND:
        struct Binary_Form one;
        one = ascii_to_bin(c, one);
        struct Binary_Form two;
        two = ascii_to_bin(k, two);
        struct Binary_Form three = xand_operate(one, two);
        answ = bin_to_ascii(three);
        break;
    case XOR:
        answ = c ^ k;
        break;
    default:
        printf("\nfuck this shit im out\n");
        answ = 'f';
        break;
    }
    return answ;
}

int get(int pos, Binary_Form* this_Binary)
{
    return this_Binary->element[pos];
}
void replace(int val, Binary_Form* this_Binary)
{
    this_Binary->element[this_Binary->slot] = val;
}

void replace(int val, int pos, Binary_Form* this_Binary)
{
    this_Binary->element[pos] = val;
}

struct Binary_Form ascii_to_bin(int letter, struct Binary_Form* binary_c)
{    
    if(letter == 1)
    {
        replace(1, binary_c);
        ++binary_c->slot;
        return *binary_c;
    }
    else
    {
        int div = letter / 2;
        --binary_c->slot;
        binary_c = ascii_to_bin(div, binary_c);
        int mod = letter % 2;
        replace(mod, binary_c);  
        ++binary_c.slot;      
        return binary_c;
    }
}

int bin_to_ascii(struct Binary_Form rev)
{
    int res = 0;
    for(int i = 0; i < 8; ++i)
    {
        res += exp2(rev.get(i));
    }    
    return res;
}

struct Binary_Form xand_operate(struct Binary_Form one, struct Binary_Form two)
{
    struct Binary_Form temp;
    for(int i = 0; i < 8; ++i)
    {
        int uno = one.get(i);
        int dos = two.get(i);
        temp.replace(xand_each(uno, dos), i);
    }
}

int xand_each(int c1, int c2)
{
    if(c1 + c2 == 2 || c1 + c2 == 0)
        return 1;
    return 0;
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
    return;

}

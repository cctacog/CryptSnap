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
        case XAND:
            answ = 0;
            Binary_Form one = INIT_BINARY_FORM;        
            one = ascii_to_bin(c, &one);
            Binary_Form two = INIT_BINARY_FORM;        
            two = ascii_to_bin(k, &two);
            Binary_Form three = xand_operate(one, two);
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

int get_O(int pos, struct Binary_Form* this_Binary)
{
    printf("get_o op");
    return this_Binary->element[pos];
}
void replace(int val, struct Binary_Form* this_Binary)
{
    printf("replace op");
    this_Binary->element[this_Binary->slot] = val;
}

void replace_pos(int val, int pos, struct Binary_Form* this_Binary)
{
    printf("replace_pos op");
    this_Binary->element[pos] = val;
}

struct Binary_Form ascii_to_bin(int letter, struct Binary_Form* binary_c)
{    
    printf("ascii_to_bin op");
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
        *binary_c = ascii_to_bin(div, binary_c);
        int mod = letter % 2;
        replace(mod, binary_c);  
        ++binary_c->slot;      
        return *binary_c;
    }
}

int bin_to_ascii(struct Binary_Form rev)
{
    printf("bin_to_ascii op");
    int res = 0;
    for(int i = 0; i < 8; ++i)
    {
        res += exp2(get_O(i, &rev));
    }    
    return res;
}

struct Binary_Form xand_operate(struct Binary_Form one, struct Binary_Form two)
{
    printf("xan_operate op");
    Binary_Form temp = INIT_BINARY_FORM;
    for(int i = 0; i < 8; ++i)
    {
        int uno = get_O(i, &one);
        int dos = get_O(i, &two);
        replace_pos(xand_each(uno, dos), i, &temp);
    }
}

int xand_each(int c1, int c2)
{
    printf("xand_each op");
    if(c1 + c2 == 2 || c1 + c2 == 0)
        return 1;
    return 0;
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

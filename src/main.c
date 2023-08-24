/*
Sophia Garcia
01-31-2023
*/
#include "encrypt_decrypt.h"
int main(int argc, char* argv[])
{
    Queue q;
    def_values_q(&q);
    insert(&q, NAND);
    insert(&q, OR);
    insert(&q, XNOR);

    while(!isEmpty_q(&q))
    {
        enum Operator op = remove_q(&q);
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

    The_Round game;
    game.code[0] = '\0';
    do
    {
        game = crypt(game);
    }
    while(game.play_again == 1);
    
    char yn[10];
    printf("\n\nWould you like to see the C ascii alphabet?: [ex: yes] ");
    gets(yn);

    if(yn[0] == 'y' || yn[0] == 'Y')
        alphabet(-1);

    printf("\nHave a nice day!\n");
    return 0;
    //code to loop until user done
    
}
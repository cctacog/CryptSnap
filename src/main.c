/*
Sophia Garcia
01-31-2023
*/
#include "encrypt_decrypt.h"
int main(int argc, char* argv[])
{    
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
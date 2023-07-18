/*
Sophia Garcia
01-31-2023
*/
#include "encrypt_decrypt.h"
int main(int argc, char* argv[])
{
    int replay = 1;
    while(replay == 1)
    {
        replay = crypt();
    }
    char yn[10];
    printf("\n\nWould you like to see the C ascii alphabet?: [ex: yes] ");
    gets(yn);

    if(yn[0] == 'y' || yn[0] == 'Y')
        alphabet(-1);

    printf("\nHave a nice day!\n");
    return replay;
    //code to loop until user done
    
}
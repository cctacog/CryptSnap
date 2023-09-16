/*
Sophia Garcia
01-31-2023
*/

#include "encrypt_decrypt.h"

The_Round crypt(The_Round *user)
{
    //prints title of program
    intro(user);
    level_one(user);
    printf("cookies\n");
    level_two(user);
    // free(code);
    // free(key);
    // free(secret); only needed when using malloc 

    return *user;
}


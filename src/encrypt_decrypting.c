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
    level_two(user);
    level_three(user);    

    return *user;
}


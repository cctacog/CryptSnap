/*
Sophia Garcia
01-31-2023
*/
#include "encrypt_decrypt.h"
int main(int argc, char* argv[])
{    

    The_Round game;    
    /*
    8 = 1000
    A = 10 = 1010
    1 XOR 1 = 0
    */   
    // game.code[0] = '\0';        
    // do
    // {
    //     game = crypt(&game);
    // }
    // while(game.play_again == 1);
    
    
    return 0;
    //code to loop until user done
    /*
    have three environments to learn from
        1. gates alone
        2. multiple gates in one go
        3. LFSR on 2-5 bit sequences (decimal values ranging from 1-31)

    how to implement per enviornment
        a. teach about each gate (7 total)
            - after each gate taught then 3 questions to answer each 
        b. layer the gates (up to three [three of two gates and three of three gates]
            - the two and three gate variations only encrypt
            - the last one is encrypt and decrypt from AND OR NAND which is only good
                for encrypt and decrypt
        c. teach the LFSR and give five examples the user has to go through
    */
}
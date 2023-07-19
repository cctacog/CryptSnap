/*
Sophia Garcia
01-31-2023
*/

#include "encrypt_decrypt.h"

The_Round crypt(const The_Round terms_)
{
    //prints title of program
    printf("\nENCRYPTION!\n\n\n");

    /*
        to keep is simple
        no malloc 
        no leaking memorey
    */
    The_Round terms;
    if(terms_.code[0] == '\0')
    {        
        printf("Enter code: ");
        gets(terms.code);
        terms.code_len = strlen(terms.code);
        printf("Enter key: ");
        gets(terms.key);   
    } 
    else
    {
        transfer(terms_, &terms);
    }
    


    /*
    encrypts each array location of secret (equal to the lengths of the code/key)
    from the operation of the code and key at the said array location
    */

    char operate[20];
    printf("\n\nWhat operation would you like to encrypt your code to key with?\n1.AND\n2. OR\n3. NAND\n4. NOR\n5. XOR\n6. XNOR\nOperator [ex: 5]: ");
    gets(operate);
    enum Operator op;
    switch(operate[0])
    {
        case '1':
            op = AND;
            break;
        case '2':
            op = OR;
            break;
        case '3':
            op = NAND;
            break;
        case '4':
            op = NOR;
            break;        
        case '5':
            op = XOR;
            break;
        case '6':
            op = XNOR;
            break;
    }    

    int iK = 0;

    for(int i = 0; (i < terms.code_len) && (terms.code[i] != '\0'); i++)
    {
        /*
        because a character cannot xor itself the
        array location will equal the said character
        */
        if(terms.code[i] == terms.key[iK] && (op == XOR || op == XNOR))
        {
            terms.secret[i] = terms.code[i];
            continue;
        }

        char s;
        s = possibleActions(op, terms.code[i], terms.key[iK]);

        terms.secret[i] = s;

        /*
        if terms.code about to end at the i+1 location
        then the secret will end at i+1
        */
        iK++;

        if(terms.code[i+1] == '\0')
            terms.secret[i+1] = '\0';
        if(terms.key[iK] == '\0')
            iK = 0;
    }

    //print final product
    printf("\nThe secret: ");

    for(int z = 0; z < terms.code_len; z++)
    {
        int num = terms.secret[z];
        if(num < 0)
            printf("%c", num);
        else printf("%c", alphabet(num));
    }

    char replay [10];

    printf("\n\nWould you care to play again?: [ex: yes]  ");
    gets(replay);

    if(replay[0] == 'y')
    {
        terms.play_again = 1;       
    }

    // free(code);
    // free(key);
    // free(secret); only needed when using malloc 

    return terms;
}


#include "encrypt_decrypt.h"
/*
Sophia Garcia
01-31-2023
*/
int crypt()
{
    //prints title of program
    printf("\nENCRYPTION!\n\n\n");

    //the string arrays of characters to hold any lengthened string (1-100)

    char* code = "";

    char* key = "";

    char* secret;

    int n1 = 0, n2 = 0;

    code = stringPtr(code, "code");
    n1 = strlen(code);
    printf("\nThe code is: %s", code);
    key = stringPtr(key, "key");
    printf("\nThe key is: %s", key);
    n2 = strlen(key);

    secret = (char*)malloc(n1 * sizeof(char));

    /*
    encrypts each array location of secret (equal to the lengths of the code/key)
    from the xor operation of the code and key at the said array location
    */

    char operate[20];
    printf("\n\nWhat operation would you like to encrypt your code to key with?\n1. AND\n2. OR\n3. NAND\n 4. NOR\n5. XOR\nOperator [ex: 5]: ");
    gets(operate);
    //char operations[5][6] = {"and", "or", "nand", "nor", "xand" , "xor"};
    enum Operator op = operate[0] - 48;
    // for(int i = 0; i < 5; i++)
    // {
    //     int q = 0;
    //     while(operate[q] != '\0')
    //     {
    //          operate[q] = tolower(operate[q]);
    //          q++;
    //     }
    //     if(strcmp(operations[i], operate) == 0)
    //      {
    //         op = i;
    //         //printf("\nFOUND\n%i\n", op);
    //      }
    // }

    int iK = 0;

    for(int i = 0; (i < n1) && (code[i] != '\0'); i++)
    {
        /*
        because a character cannot xor itself the
        array location will equal the said character
        */
        if(code[i] == key[iK])
        {
            secret[i] = code[i];
            continue;
        }

        char s;
        s = possibleActions(op, code[i], key[iK]);

        secret[i] = s;

        /*
        if code about to end at the i+1 location
        then the secret will end at i+1
        */
        iK++;

        if(code[i+1] == '\0')
            secret[i+1] = '\0';
        if(key[iK] == '\0')
            iK = 0;
    }

    //print final product
    printf("\nThe secret: ");

    for(int z = 0; z < n1; z++)
    {
        int num = secret[z];
        if(num < 0)
            printf("%c", num);
        else printf("%c", alphabet(num));
    }

    char yn[10];

    printf("\n\nWould you like to see the C ascii alphabet?: ");
    gets(yn);

    if(yn[0] == 'y' || yn[0] == 'Y')
        alphabet(-1);

    printf("\nHave a nice day!\n");

    free(code);
    free(key);
    free(secret);

    return 0;
}


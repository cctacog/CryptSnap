#include "encrypt_decrypt.h"


int encrypt_decrypt()
{
    //prints title of program
    printf("\nENCRYPTION!\n\n\n");

    //the string arrays of characters to hold any lengthened string (1-100)

    char* code = "";

    char* key = "";

    char* secret;

    int n1 = 0, n2 = 0;

    code = stringPtr(code);
    n1 = strlen(code);
    printf("\nThe code is: %s", code);
    key = stringPtr(key);
    printf("\nThe key is: %s", key);
    n2 = strlen(key);

    secret = (char*)malloc(n1 * sizeof(char));

    /*
    encrypts each array location of secret (equal to the lengths of the code/key)
    from the xor operation of the code and key at the said array location
    */

    char operate[20];
    printf("\n\nWhat operation would you like to encrypt your code to key with?\n(AND/OR/NAND/NOR/XOR): ");
    gets_s(operate);
    char operations[5][6] = {"and", "or", "nand", "nor", "xor"};
    int op = -1;
    for(int i = 0; i < 5; i++)
    {
        int q = 0;
        while(operate[q] != '\0')
        {
             operate[q] = tolower(operate[q]);
             q++;
        }
        if(strcmp(operations[i], operate) == 0)
         {
            op = i;
            //printf("\nFOUND\n%i\n", op);
         }
    }

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
        if((key[iK] > 47 && key[iK] < 58) || (code[i] > 47 && code[i] < 58))
            s = num_let(op, code[i], key[iK]);
        else s = possibleActions(op, code[i], key[iK]);

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
        else printf("%c", char_alphabet(num));
    }

    char yn[10];

    printf("\n\nWould you like to see the C ascii alphabet?: ");
    gets(yn);

    if(yn[0] == 'y' || yn[0] == 'Y')
        char_alphabet(-1);

    printf("\nHave a nice day!\n");

    free(code);
    free(key);
    free(secret);

    return 0;
}


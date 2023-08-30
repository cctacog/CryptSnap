#include "reference.h"
#include "crypt_helper.h"
int main()
{
    int a = 0;
    int b = 0;
    int user_result = 0;
    int result = 0;
    enum Operator op = NONE;    
    do
    {
        printf("Pick a logic gate: \n1. AND\n2. OR\n3. NAND\n4. NOR\n5. XOR\n6. XNOR\n[ex: 1]: ");
        switch(op)
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
            default:
                perror("invalid");
                return 0;            
        }
    printf("Pick an even number [0-9]: ");
    gets(a);
    printf("Pick an odd number [0-9]: ");
    gets(b);
    a -= 48;
    b -= 48;
    result = possibleActions(op, a, b);    
    printf("What do you think the answer will be?:");
    gets(user_result);
    user_result -= 48;
    if(result == user_result)
    {
        printf("Yay you win!");        
    }
    else 
    {
        printf("Oof thats not right! The answer was: %i", result);        
    }
    char answ[10];
    printf("play again? [ex: no]: ");
    gets(answ);
    if(answ[0] != 'y' || answ[0] != 'Y')
    {
        op = NONE;
    }

    } while (op != NONE);
    
    return 0;
}
#ifndef STACK_OPS
#define STACK_OPS

#include "crypt_helper.h"

typedef struct Stack//stack with a max capacity of 20 elements
{
    int top;
    unsigned capacity;
    enum Operator array[20];    
} Stack;
//nothing allocated therefore nothing needs free!

//stack functions
int isFull(const Stack *stack);
int isEmpty(const Stack *stack);
void push(Stack *stack, enum Operator op);
enum Operator pop(Stack *stack);
enum Operator peek(const Stack *stack);

#endif
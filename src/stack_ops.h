#ifndef STACK_OPS
#define STACK_OPS

#include "reference.h"

typedef struct Stack//stack with a max capacity of 20 elements
{
    int top;
    unsigned capacity;
    enum Operator arr[MAX];    
} Stack;
//nothing allocated therefore nothing needs free!

//stack functions
void def_values_s(Stack *stack);
int isFull_s(const Stack *stack);
int isEmpty_s(const Stack *stack);
void push(Stack *stack, enum Operator op);
enum Operator pop(Stack *stack);
enum Operator peek_s(const Stack *stack);

#endif
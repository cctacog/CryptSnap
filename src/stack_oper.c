#include "stack_ops.h"

void def_values_s(Stack *stack)
{
    stack->capacity = MAX;
    stack->top = 0;
}

int isFull_s(const Stack *stack)
{
    return stack->top == stack->capacity;
}

int isEmpty_s(const Stack *stack)
{
    return stack->top == 0;
}

void push(Stack *stack, enum Operator op)
{
    printf("start\n");
    if(isFull_s(stack))
    {    
        printf("nope\n");
        return;
    }
    printf("pushing\n");
    printf("%i\n", stack->top);
    ++(stack->top);
    printf("%i\n", stack->top);
    stack->arr[stack->top] = op;    
    printf("PUSHED\n");
}
enum Operator pop(Stack *stack)
{
    if(isEmpty_s(stack))
        return INT_MIN;
    return stack->arr[stack->top--];    
}

enum Operator peek_s(const Stack *stack)
{
    if(isEmpty_s(stack))
        return INT_MIN; 
    return stack->arr[stack->top];
}
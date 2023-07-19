#include "stack_ops.h"

int isFull(const Stack *stack)
{
    return stack->top == stack->capacity - 1;
}
int isEmpty(const Stack *stack)
{
    return stack->top == -1;
}
void push(Stack *stack, enum Operator op)
{
    if(isFull(stack))
        return;
    stack->array[++stack->top] = op;
    printf("PUSHED\n");
}
enum Operator pop(Stack *stack)
{
    if(isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];    
}
enum Operator peek(const Stack *stack)
{
    if(isEmpty(stack))
        return INT_MIN; 
    return stack->array[stack->top];
}
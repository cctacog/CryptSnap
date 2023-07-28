#include "stack_ops.h"

int isFull_s(const Stack *stack)
{
    return stack->top == stack->capacity - 1;
}
int isEmpty_s(const Stack *stack)
{
    return stack->top == -1;
}
void push(Stack *stack, enum Operator op)
{
    if(isFull_s(stack))
        return;
    stack->arr[++stack->top] = op;
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
#include "queue_ops.h"

void def_values_q(Queue * queue)
{
    queue->front = 0;
    queue->rear = 1;
    queue->item_Count = 0;
}

int isFull_q(const Queue *queue)
{
    return queue->rear == queue->front;
}

int isEmpty_q(const Queue *queue)
{
    return queue->item_Count == 0;
}

int size(const Queue *queue)
{
    return queue->item_Count;
}

void insert(Queue *queue, enum Operator op)
{
    if(isFull_q(queue))
    {        
        return;
    }
    queue->array[queue->rear-1] = op;
    queue->rear = (queue->rear + 1) % MAX;    
    queue->item_Count = queue->item_Count + 1;
    printf("pushed\n");
}

enum Operator remove_q(Queue *queue)
{
    if(isEmpty_q(queue))
        return INT_MIN;
    enum Operator current_front = queue->array[queue->front];
    queue->front = (queue->front + 1) % MAX;
    queue->item_Count = queue->item_Count - 1;
    return current_front;
}

enum Operator peek_q(const Queue *queue)
{
    if(isEmpty_q(queue))
        return INT_MIN;
    return queue->array[queue->front];
}
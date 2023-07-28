#include "queue_ops.h"

int isFull_q(const Queue *queue)
{
    return queue->item_Count == MAX;
}
int isEmpty_q(const Queue *queue)
{
    return queue->item_Count == 0;
}
int size_q(const Queue *queue)
{
    return queue->item_Count;
}
void insert_q(Queue *queue, enum Operator op)
{
    if(isFull_q(queue))
        return;
    queue->rear = (queue->rear + 1) % MAX;
    queue->array[queue->rear] = op;
    queue->item_Count = queue->item_Count + 1;
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
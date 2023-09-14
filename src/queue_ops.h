#ifndef QUEUE_OPS
#define QUEUE_OPS

#include "reference.h"

typedef struct Queue
{
    enum Operator array[MAX];
    int front;
    int rear;
    int item_Count;
} Queue;

void def_values_q(Queue * queue);
int isFull_q(const Queue *queue);
int isEmpty_q(const Queue *queue);
int size(const Queue *queue);
void insert(Queue *queue, const enum Operator op);
enum Operator remove_q(Queue *queue);
enum Operator peek_q(const Queue *queue);


#endif
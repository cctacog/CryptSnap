#ifndef QUEUE_OPS
#define QUEUE_OPS

#define MAX 20
#include "reference.h"

typedef struct Queue
{
    enum Operator array[MAX];
    int front;
    int rear;
    int item_Count;
} Queue;

int isFull_q(const Queue *queue);
int isEmpty_q(const Queue *queue);
int size_q(const Queue *queue);
void insert_q(Queue *queue, enum Operator op);
enum Operator remove_q(Queue *queue);
enum Operator peek_q(const Queue *queue);


#endif
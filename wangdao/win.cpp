#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>

// 顺序队列
#define MaxSize 50
typedef struct
{
    int data[50];
    int front, rear;
}*SqQueue;

void InitQueue(SqQueue &Q) {
    Q->front = 0;
    Q->rear = 0;
}

bool QueueEmpty(SqQueue Q) {
    return Q->front == Q->rear;
}

bool EnQueue(SqQueue &Q, int x) {
    if (Q->rear == MaxSize)
      return false;
    Q->data[Q->rear++] = x;
    return true;
}

bool DeQueue(SqQueue &Q, int &x) {
    if (QueueEmpty(Q))
        return false;
    x = Q->data[Q->front++];
    return true;
}

bool GetHead(SqQueue Q, int &x) {
    if (QueueEmpty(Q))
        return false;
    x = Q->data[Q->front];
    return true;
}
int main()
{

}
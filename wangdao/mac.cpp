#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>

// 链式队列
typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct {
    LinkNode *front, *rear;
}*LinkQueue;

void InitQueue(LinkQueue &Q) {
    Q->front = Q->rear = (LinkNode*)malloc(sizeof(LinkNode));
    Q->front = NULL;
}

bool QueueEmpty(LinkQueue Q) {
    return Q->front == Q->rear;
}

bool EnQueue(LinkQueue &Q, int x) {
    LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = x;
    Q->rear->next = p;
    Q->rear = p;
    p->next = NULL;
    return true;
}

bool DeQueue(LinkQueue &Q, int &x) {
    if (QueueEmpty(Q))
        return false;
    LinkNode *p = Q->front->next;
    x = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return true;
}

bool GetHead(LinkQueue Q, int &x) {
    if (QueueEmpty(Q))
        return false;
    x = Q->front->data;
    return true;
}

int main()
{
    SeqList L;
    InitList(L);
    List_TailInsert(L);
    PrintList(L);
    printf("%d", FindMinDistance(L));
    return 0;
}
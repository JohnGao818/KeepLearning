#include <stdio.h>
#include <stdlib.h>

// 单链链表
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode, *LinkList;

LinkList List_HeaderInsert(LinkList &L) {
    LNode *s; int x;
    L=(LinkList)malloc(sizeof(LNode)); // 创建头结点
    L->next = NULL;
    scanf("%d", &x);
    while (x != 9999) {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        L->next = s;
        scanf("%d", &x);
    }
    return L;
}

LinkList List_TailInsert(LinkList &L) {
    LNode *s, *t; int x;
    L=(LinkList)malloc(sizeof(LNode));
    t = L;
    scanf("%d", &x);
    while (x != 9999)
    {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        t->next = s;
        t = s;
        scanf("%d", &x);
    }
    t->next = NULL;
    return L;
}

LNode *GetElem(LinkList &L, int x) {
    if (x < 1) {
        return NULL;
    }
    LNode *s = L->next; int i = 0;
    while (s != NULL && ++i < x)
    {
        s = s->next;
    }
    return s;
}

LNode *LocateElem(LinkList &L, int value) {
    LNode *s = L->next;
    while (s != NULL && s->data != value)
    {
        s = s->next;
    }
    return s;
}

LinkList insertElem(LinkList &L, int index, int value) {
    if (index < 1) {
        return L;
    }
    LNode *s, *c;
    c = (LNode*)malloc(sizeof(LNode));
    c->data = value;
    if (index == 1) {
        s = L;
    } else {
        s = GetElem(L, index - 1);
    }
    if (s == NULL) {
        return L;
    }
    c->next = s->next;
    s->next = c;
    return L;
}

bool deleteElem(LinkList &L, int index) {
    if (index < 1) {
        return false;
    }
    LNode *s, *q;
    if (index == 1) {
        s = L;
    } else {
        s = GetElem(L, index - 1);
    }
    
    if (s == NULL || s->next == NULL) {
        return false;
    }
    q = s->next;
    s->next = q->next;
    free(q);
    return true;
}

int getLength(LinkList &L) {
    int length = 0;
    LNode *s = L->next;
    while (s != NULL)
    {
        s=s->next;
        length++;
    }
    return length;
}

void printLinkList(LinkList &L) {
    LNode *s = L->next;
    while (s != NULL)
    {
        printf("%d, ", s->data);
        s = s->next;
    }
    printf("\n");
}

int main()
{
    LinkList L;
    List_TailInsert(L);
    printLinkList(L);
    printf("GetElem = %d \n", GetElem(L, 3)->data);
    printf("LocateElem = %d \n", LocateElem(L, 3)->data);
    insertElem(L, 1, 100);
    printLinkList(L);
    deleteElem(L, 1);
    printLinkList(L);
    printf("total length = %d \n", getLength(L));
    return 0;
}
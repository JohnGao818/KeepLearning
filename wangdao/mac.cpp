#include <stdio.h>
#include <stdlib.h>

#define MaxSize 50
// 顺序表
typedef struct SeqList
{
    int data[MaxSize];
    int length;
} SeqList;

void InitList(SeqList &L)
{
    L.length = 0;
}

int Length(SeqList L)
{
    return L.length;
}

int LocateElem(SeqList L, int e)
{
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1;
    return 0;
}

int GetElem(SeqList L, int i)
{
    return L.data[i];
}

bool ListInsert(SeqList &L, int i, int e)
{
    if (i < 1 || i > L.length + 1)
        return false;
    if (L.length >= MaxSize)
        return false;
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool ListDelete(SeqList &L, int i, int &e)
{
    if (i < 1 || i > L.length + 1)
        return false;
    e = L.data[i - 1];
    for (int j = i; j < L.length; j--)
        L.data[j - 1] = L.data[j];
    L.length--;
    return true;
}

void PrintList(SeqList &L)
{
    for (int i = 0; i < L.length; i++) {
        printf("%d, ", L.data[i]);
    }
    printf("\n");
}

bool Empty(SeqList L)
{
    return L.length == 0;
}

// 销毁线性表，释放线性表L所占用的内存空间
void DestroyList(SeqList &L)
{
    L.length = 0;
}

void List_TailInsert(SeqList &L) {
    int x;
    scanf("%d", &x);
    while (x != 9999)
    {
        L.data[L.length++] = x;
        scanf("%d", &x);
    }
}

void DeleteElem(SeqList &L, int e)
{
    
}

int main()
{
    int temp = 3;
    SeqList L;
    InitList(L);
    List_TailInsert(L);
    PrintList(L);
    Reverse(L);
    PrintList(L);
    return 0;
}
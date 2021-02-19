### reverse
```
typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

void reverse(LinkList L)
{
    if (!L == NULL && !L->next == NULL)
    {
        LNode *tail = L->next;
        LNode *p = tail->next;
        LNode *q;
        while (p != NULL)
        {
            q = p->next;
            p->next = L->next;
            L->next = p;
            tail -> next = q;
            p = q;
        }
    }
}
```

####
```
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
    BiTree data[MAXSIZE];
    int front, rear;
}Queue;

void InitQueue(Queue &q) {
    q.front = 0;
    q.rear = 0;
}

bool QueueEmpty(Queue q) {
    return q.rear == q.front;
}

bool EnQueue(Queue &q, BiTree node) {
    if (q.front == MAXSIZE) {
        return false;
    }
    q.data[q.front] = node;
    q.front++;
    return true;
}

bool DeQueue(Queue &q, BiTree &node) {
    if (q.front == q.rear) {
        return false;
    }
    node = q.data[q.rear];
    q.rear += 1;
    return true;
}

int findNode(BiTree T) {
    Queue q; InitQueue(q);
    BiTNode *node;
    int count = 0;
    EnQueue(q, T);
    while(DeQueue(q, node)) {
        if ((node->lchild == NULL && node->rchild != NULL) || (node->lchild != NULL && node->rchild == NULL)) {
            count++;
        }
        if (node->lchild != NULL) {
            EnQueue(q, node->lchild);
        }
        if (node->rchild != NULL) {
            EnQueue(q, node->rchild);
        }
    }
    return count;
}
```

#### merge two symmetric matrix
```

typedef struct 
{
    int data[MAXSIZE];
    int length;
    int site;
}SMatrix;

void add(SMatrix A, SMatrix B, SMatrix C) {
    C.length = A.length;
    C.site = A.site;
    for(int i = 0; i < A.length; i++) {
        C.data[i] = A.data[i] + B.data[i];
    }
}
```
#### get height and node count
```
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

int getNodeCount(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        return getNodeCount(T->lchild) + getNodeCount(T->rchild) + 1;
    }
}

int getHeight(BiTree T) {
    BiTree queue[MAXSIZE];
    BiTNode *s;
    int height = 0, flag;
    int front = 0,rear = 0;
    queue[rear++] = T;
    flag = rear;
    while(front != rear) {
        s = queue[front++];
        if (s->lchild != NULL) {
            queue[rear++] = s->lchild;
        }
        if (s->rchild != NULL) {
            queue[rear++] = s->rchild;
        }
        if (front == flag) {
            height++;
            flag = rear;
        }
    }
    return height;
}
```
#### delete arc from ALGraph
```

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextArc;
}ArcNode;

typedef struct VNode {
    char vex;
    ArcNode *firstArc;
}VNode, AdjList;

typedef struct {
    AdjList adjList[MAXSIZE];
    int vertexNum, arcNum;
}ALGraph;

bool deleteArc(ALGraph &G, char a, char b) {
    VNode *start; int end;
    bool startFlag = false, endFlag = false;
    for (int i = 0; i < G.vertexNum; i++) {
        if (G.adjList[i].vex == a) {
            start = &(G.adjList[i]);
            startFlag = true;
        }
        if (G.adjList[i].vex == a) {
            end = i;
            endFlag = true;
        }
    }
    if (!startFlag || !endFlag) {
        return false;
    }
    ArcNode *p = start->firstArc;
    if (p->adjvex == end) {
        start->firstArc = p->nextArc;
        free(p);
        return true;
    }
    while(p->nextArc != NULL) {
        if (p->nextArc->adjvex == end) {
            ArcNode *q = p->nextArc;
            p->nextArc = q->nextArc;
            free(q);
            return true;
        }
        p = p->nextArc;
    }
    return false;
}
```


#### convert ALGraph to MGraph
```
#define MAXSIZE 100
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextArc;
} ArcNode;

typedef struct VNode
{
    char data;
    ArcNode *firstArc;
} VNode, AdjList[MAXSIZE];
typedef struct
{
    AdjList adjlist;
    int vertexNum, arcNum;
} ALGraph;

typedef struct
{
    char Vertex[MAXSIZE];
    int Edge[MAXSIZE][MAXSIZE];
    int vertexNum, arcNum;
} MGraph;

void convert(ALGraph AG, MGraph MG)
{
    MG.vertexNum = AG.vertexNum;
    MG.arcNum = 0;
    for (int i = 0; i < AG.vertexNum; i++) {
        MG.Vertex[i] = AG.adjlist[i].data;
        ArcNode *arcnode = (AG.adjlist[i]).firstArc;
        while(arcnode != NULL) {
            MG.Edge[i][arcnode->adjvex] = 1;
            arcnode = arcnode->nextArc;
            MG.arcNum++;
        }
    }
}
```

#### BFS
```
typedef struct {
    int data[MAXSIZE];
    int front, rear;
}Queue;

void InitQueue(Queue &q) {
    q.front = 0;
    q.rear = 0;
}

bool QueueEmpty(Queue q) {
    return q.front == q.rear;
}

bool EnQueue(Queue &q, int x) {
    if (q.rear == MAXSIZE) {
        return false;
    }
    q.data[q.rear++] = x;
    return true;
}

bool DeQueue(Queue &q, int &x) {
    if (q.rear == q.front) {
        return false;
    }
    x = q.data[q.front++];
    return true;
}


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
// is vertex x and y adjacented;
bool Adjacent(ALGraph G, char x, char y) {

}
// find neighbors from vertex v
VNode *Neighbors(ALGraph G, char v) {

}

bool InsertVertex(ALGraph &G, char v) {
    if (G.vertexNum >= MAXSIZE) {
        return false;
    }
    VNode *node = (VNode*)malloc(sizeof(VNode));
    node->vex = v;
    node->firstArc = NULL;
    G.adjList[G.vertexNum++] = *node;
    return true;
}

bool DeleteVertex(ALGraph &G, char v) {
    
}

int FirstNeighbor(ALGraph &G, char v) {
    for (int i=0; i < G.vertexNum; i++) {
        if (G.adjList[i].vex == v) {
            return i;
        }
    }
    return -1;
}

int NextNeighbor(ALGraph &G, char v, char y) {
    VNode vnode;
    int yindex;
    for (int i=0; i < G.vertexNum; i++) {
        if (G.adjList[i].vex == v) {
            vnode = G.adjList[i];
        }
        if (G.adjList[i].vex == y) {
            yindex = i;
        }
    }
    ArcNode *arc = vnode.firstArc;
    while(arc != NULL && arc->adjvex != yindex) {
        arc = arc->nextArc;
    }
    if (arc == NULL) {
        return -1
    } else {
        return arc->adjvex;
    }
}

void visit(ALGraph G, int v) {
    printf(&G.adjList[v].vex);
}

bool visited[MAXSIZE];
Queue Q;

void BFS(ALGraph G, int start) {
    visit(G, start);
    visited[start] = true;
    InitQueue(Q);
    EnQueue(Q, start);
    int x;
    while(!QueueEmpty(Q)) {
        DeQueue(Q, x);
        // visit(G, x);
        // visited[x] = true;
        for (int w = FirstNeighbor(G, start); w>=0; w=NextNeighbor(G, start, w)) {
            if (!visited[w]) {
                visit(G, start);
                visited[start] = true;
                EnQueue(Q, w);
            }
        }
    }
}

void BFSTraverse(ALGraph G) {
    for(int i = 0; i < MAXSIZE; i++)  {
        visited[i] = false;
    }
    for (int i = 0; i < G.vertexNum; i++) {
        if (!visited[i]) {
            BFS(G, i);
        }
    }
}
```

#### DFS
```

typedef struct ArcNode {
    int vertex;
    struct ArcNode *nextArc;
}ArcNode;

typedef struct VNode {
    char data;
    ArcNode *firstArc;
}VNode, AdjList;

typedef struct {
    AdjList adjList[MAXSIZE];
    int vertexNum, arcNum;
}ALGraph;

bool Adjacent(ALGraph G, char x, char y) {

}

bool InsertVertex(ALGraph &G, char v) {

}

bool DeleteVertex(ALGraph &G, char v) {

}

bool AddEdge(ALGraph &G, char x, char y) {

}

bool RemoveEdge(ALGraph &G, char x, char y) {

}

int *Neighbors(ALGraph &G, char v) {

}

int FirstNeighbor(ALGraph G, char v) {

}

int NextNeighbor(ALGraph G, char x, char y) {

}

void visit(ALGraph G, int v) {

}


bool visited[MAXSIZE];
void DFSTraverse(ALGraph G) {
    for (int i=0; i < G.vertexNum; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < G.vertexNum; i++) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
    
}

void DFS(ALGraph G, int v) {
    visit(G, v);
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}
```

#### Find Min Distance
```

typedef struct ArcNode {
    int vertex;
    struct ArcNode *nextArc;
}ArcNode;

typedef struct VNode {
    char data;
    ArcNode *firstArc;
}VNode, AdjList;

typedef struct {
    AdjList adjList[MAXSIZE];
    int vertexNum, arcNum;
}ALGraph;

bool Adjacent(ALGraph G, char x, char y) {

}

bool InsertVertex(ALGraph &G, char v) {

}

bool DeleteVertex(ALGraph &G, char v) {

}

bool AddEdge(ALGraph &G, char x, char y) {

}

bool RemoveEdge(ALGraph &G, char x, char y) {

}

int *Neighbors(ALGraph &G, char v) {

}

int FirstNeighbor(ALGraph G, char v) {

}

int NextNeighbor(ALGraph G, char x, char y) {

}

void visit(ALGraph G, int v) {

}
typedef struct Queue {
    int data;
    int front, rear;
}Queue;

void InitQueue(Queue &q) {
    q.front = 0;
    q.rear = 0;
}

bool QueueEmpty(Queue q) {
    return q.front == q.rear;
}

bool EnQueue(Queue &q, int x) {
    if (q.rear == MAXSIZE) {
        return false;
    }
    q.data[q.rear++] = x;
    return true;
}

bool DeQueue(Queue &q, int &x) {
    if (q.rear == q.front) {
        return false;
    }
    x = q.data[q.front++];
    return true;
}

bool visited[MAXSIZE];
int d[MAXSIZE];
int Find_Min_Distance(ALGraph G, int v) {
    for (int i = 0; i < G.vertexNum; i++) {
        d[i] = 0;
    }
    Queue Q;InitQueue(Q);
    EnQueue(Q, v);visited[v] = true;
    while(!QueueEmpty(Q)) {
        DeQueue(Q, v);
        for(int w=FirstNeighbor(G, v); w >=0; w=NextNeighbor(G, v, w)) {
            if (!visited[w]) {
                DeQueue(Q, w);
                visited[w] = true;
                d[w] = d[v] + 1;
            }
        }
    }
}
```

#### Topo Logical Sort
```

typedef struct ArcNode {
    int vertex;
    struct ArcNode *nextArc;
}ArcNode;

typedef struct VNode {
    char data;
    ArcNode *firstArc;
}VNode, AdjList;

typedef struct {
    AdjList adjList[MAXSIZE];
    int vertexNum, arcNum;
}ALGraph;

bool Adjacent(ALGraph G, char x, char y) {

}

bool InsertVertex(ALGraph &G, char v) {

}

bool DeleteVertex(ALGraph &G, char v) {

}

bool AddEdge(ALGraph &G, char x, char y) {

}

bool RemoveEdge(ALGraph &G, char x, char y) {

}

int *Neighbors(ALGraph &G, char v) {

}

int FirstNeighbor(ALGraph G, char v) {

}

int NextNeighbor(ALGraph G, char x, char y) {

}

void visit(ALGraph G, int v) {

}
typedef struct Stack {
    int data[MAXSIZE];
    int top;
}Stack;

void InitStack(Stack &S) {
    S.top = -1;
}

bool StackEmpty(Stack S) {
    return S.top == -1;
}

bool push(Stack &S, int x) {
    if (S.top >= MAXSIZE) {
        return false;
    }
    S.data[++S.top] = x;
    return true;
}

bool pop(Stack &S, int x) {
    if (S.top == -1) {
        return false;
    }
    x = S.data[q.front--];
    return true;
}

bool visited[MAXSIZE];
int d[MAXSIZE];
int indegree[MAXSIZE];
int print[MAXSIZE];
bool TopologicalSort(ALGraph G) {
    Stack S; InitStack(S); int p, count = 0;
    for(int i = 0; i < G.vertexNum; i++) {
        if (indegree[i] == 0) {
            push(S, i);
        }
    }
    while(!StackEmpty(S)) {
        pop(S, p);
        print[count++] = p;
        for(ArcNode *q = G.adjList[p].firstArc; q != NULL; q = q->nextArc) {
            if(--indegree[q->vertex] == 0) {
                push(S, q->vertex);
            }
        }
    }
    return count == G.vertexNum;
}
```
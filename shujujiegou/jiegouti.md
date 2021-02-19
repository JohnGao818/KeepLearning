####
```
  typedef struct {
    int data[MAXSIZE];
    int length;
  }SqList;
```
####

```
  typedef struct LinkNode {
    int data;
    struct LinkNode *next;
  }LinkNode,*LinkList;
```
###
InitStack(&S);
StackEmpty(S);
Push(&S, data);
Pop(&S, &data);
GetTop(&S, &data);
DestoryStack(&S);

```
  typedef struct {
    int data[MAXSIZE];
    int top;
  }SqStack;
```
```
  typedef struct LNode{
    int data[MAXSIZE];
    struct LNode *next;
  }*LinkStack;
```

####
InitQueue(&Q);
QueueEmpty(Q);
EnQueue(&Q, data);
DeQueue(&Q, &data);
GetHead(Q, &data);
DestroyQueue(&Q);

```
  typedef struct {
    int data[MAXSIZE];
    int front, rear;
  }SqQueue;
```
```
  typedef struct {
    int data[MAXSIZE];
    int front, rear;
    int tag;
  }CyQueue;
```

```
  typedef struct{
    int data;
    struct LNode *next;
  }LNode;
```
```
  typedef struct {
    LNode *front, *rear;
  }*LQueue;
```

#### LinkTree
typedef struct BiNode{
  int data;
  struct BiNode *lchild, *rchild;
}BiNode, *BiTree;

#### parents expression forest
```
  typedef struct {
    int data;
    int parent;
  }PNode;
  typedef struct {
    PNode nodes[MAXSIZE];
    int n;
  }PTree;
```

#### child expression forest
```
  typedef struct CSNode {
    int data;
    struct CSNode *firstchild, *nextbrother
  }
```

#### Matrix Graph
```
  #define MAXSIZE 100 
  typedef struct {
    char Vertex[MAXSIZE];
    int Edge[MAXSIZE][MAXSIZE];
    int vertexNum, arcNum;
  }MGraph;
```

#### AlGraph

```
  #define MAXSIZE 100
  typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextArc;
  }ArcNode;
  typedef struct VNode {
    char data;
    struct ArcNode *firstArc;
  }VNode, AdjList[MAXSIZE];
  typedef struct {
    AdjList adjlist;
    int vertexNum, arcNum;
  }ALGraph;
```
Adjacent(G,x,y);
Neighbors(G,v);
InsertVertex(G,v);
DeleteVertex(G,v);
AddEdge(G,x,y);
RemoveEdge(G,x,y);
FirstNeighbor(G,v);
NextNeighbor(G,x,y);
Get_edge_value(G,x,y);
Set_edge_value(G,x,y);


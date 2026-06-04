#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

typedef struct EdgeNode
{
    int adjvex;
    int data; // 存储边的编号
    struct EdgeNode *next;
} EdgeNode;

typedef struct
{
    int data;
    EdgeNode *first;
} VertexNode;

typedef struct
{
    VertexNode vertices[SIZE];
    int vertexCount;
    int edgeCount;
} ALGraph;

void initALGraph(ALGraph *g, int vertexCount, int EdgeCount); // 创建无向图
EdgeNode *newEdgeNode(int data, int adjvex); // 创建新的边 并且设置对应的编号
int insertEdgeAL(ALGraph *g, int data, int from, int to); // 插入对应的边以及对应的编号 这里是作为对于无向图的插入 所以两边均需要进行插入 并且这里需要按照字母序进行插入
void insertordered(EdgeNode **head, EdgeNode *node); // 按照数字序进行插入
void DFSUtil(ALGraph *g, int v, int visited[], int to); //深度优先搜索基本单元 找到前往to的所有路径
void travelDFS(ALGraph *g, int from, int obj); // 深度优先搜索调用 搜索从from到to的所有路径
void print(); // 打印搜索到的路径 并进行重置

int path[512];
int pathlen;

int main(void)
{
    int vertexCount;
    int edgeCount;
    pathlen = 0;

    scanf("%d%d", &vertexCount, &edgeCount);

    ALGraph *g = (ALGraph *)malloc(sizeof(ALGraph));
    initALGraph(g, vertexCount, edgeCount);

    for (int num = 0; num < edgeCount; num++)
    {
        int rubbish; int from; int to;
        scanf("%d%d%d", &rubbish, &from, &to);
        insertEdgeAL(g, rubbish, from, to);
    }

    travelDFS(g, 0, vertexCount - 1);

    return 0;
}

void initALGraph(ALGraph *g, int vertexCount, int EdgeCount)
{
    g -> edgeCount = EdgeCount;
    g -> vertexCount = vertexCount;

    for (int num = 0; num < vertexCount; num++)
    {
        g -> vertices[num].first = NULL;
        g -> vertices[num].data = num; // 存储对应数字的标号
    }
}

EdgeNode *newEdgeNode(int data, int adjvex)
{
    EdgeNode *result = (EdgeNode *)malloc(sizeof(EdgeNode));

    result -> data = data;
    result -> adjvex = adjvex;
    result -> next = NULL;

    return result;
}

int insertEdgeAL(ALGraph *g, int data, int from, int to)
{
    EdgeNode *edge1 = newEdgeNode(data, to);
    EdgeNode *edge2 = newEdgeNode(data, from);
    int flag = 0;

    for (int num = 0; num < g -> vertexCount; num++)
    {
        if (g -> vertices[num].data == from)
        {
            insertordered(&(g -> vertices[num].first), edge1);
            flag++;
        }

        if (g -> vertices[num].data == to)
        {
            insertordered(&(g -> vertices[num].first), edge2);
            flag++;
        }
    }

    if (flag == 2)
        return 1;
    else
        return 0;

}

void insertordered(EdgeNode **head, EdgeNode *node)
{
    EdgeNode *p = *head;
    EdgeNode *pre = NULL;

    while (p != NULL && p -> data <= node -> data)
    {
        pre = p;
        p = p -> next;
    }

    if (pre == NULL)
    {
        node -> next = *head;
        *head = node;
    }
    else
    {
        node -> next = p;
        pre -> next = node;
    }

}

void DFSUtil(ALGraph *g, int v, int visited[], int to)
{
    EdgeNode *p;
    visited[v] = 1;

    for (p = g -> vertices[v].first; p != NULL; p = p -> next)
    {
        if (p -> adjvex == to)
        {
            path[pathlen++] = p -> data;
            print(to);
            pathlen--;
            return ;
        }

        if (visited[p -> adjvex] == 0)
        {    
            path[pathlen++] = p -> data;
            DFSUtil(g, p -> adjvex, visited, to);
        }
    }
    pathlen--;
    visited[v] = 0;
}

void print()
{
    for (int item = 0; item < pathlen; item++)
    {
        printf("%d ", path[item]);
    }
    printf("\n");

    pathlen--;
}

void travelDFS(ALGraph *g, int from, int obj)
{
    int visited[SIZE] = {0};
    
    DFSUtil(g, from, visited, obj);

    return ;
}
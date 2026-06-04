#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

typedef struct EdgeNode
{
    
    int adjvex; // 连接到的点
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

typedef struct 
{
    int data[SIZE];
    int front;
    int rear;
} Queue;

void initALGraph(ALGraph *g, int vertexCount, int EdgeCount); // 创建无向图 会初始化顶点
EdgeNode *newEdgeNode(int adjvex); // 创建新的边
int insertEdgeAL(ALGraph *g, int from, int to); // 插入对应的边 这里编写作为无向图的 同时两端插入
void insetordered(EdgeNode **head, EdgeNode *node); // 有序插入对应的顶点 头插法不适合于正常题目
void RemoveVertex(ALGraph *g, int index); // 删除指定节点的编号
void DFSUtil(ALGraph *g, int v, int visited[]); // 深度优先搜索的基本单元
void travelDFS(ALGraph *g); // 深度优先搜索调用器
void BFSUtil(ALGraph *g, int start, int visited[]); // 广度优先搜索基本单元
void travelBFS(ALGraph *g); // 广度优先搜索调用器
void visitVertex(ALGraph *g, int v); // 打印顶点
void initQueue(Queue *q); // 初始化循环队列
int isQueueEmpty(Queue *q); // 判断队列是否为空
void enQueue(Queue *q, int x); // 插入队列中的元素
int deQueue(Queue *q, int *x); // 弹出队列中的元素


int main(void)
{
    int VertexCount; // 记录顶点个数
    int EdgeCount; // 记录边个数
    int removed; // 被删除的顶点

    ALGraph *g = (ALGraph *)malloc(sizeof(ALGraph));

    scanf("%d%d", &VertexCount, &EdgeCount);
    initALGraph(g, VertexCount, EdgeCount);

    for (int num = 0; num < EdgeCount; num++)
    {
        int first; int second;
        scanf("%d%d", &first, &second);
        insertEdgeAL(g, first, second);
    }

    travelDFS(g);
    travelBFS(g);

    scanf("%d", &removed);

    RemoveVertex(g, removed);

    travelDFS(g);
    travelBFS(g);

    return 0;
}

void initALGraph(ALGraph *g, int vertexCount, int EdgeCount)
{
    g -> edgeCount = EdgeCount;
    g -> vertexCount = vertexCount;

    for (int num = 0; num < vertexCount; num++)
    {
        g -> vertices[num].first = NULL;
        g -> vertices[num].data = num; // 存储对应的数字标号
    }
}

EdgeNode *newEdgeNode(int adjvex)
{
    EdgeNode *result = (EdgeNode *)malloc(sizeof(EdgeNode));

    result -> adjvex = adjvex;
    result -> next = NULL;

    return result;
}

int insertEdgeAL(ALGraph *g, int from, int to)
{
    EdgeNode *edge1 = newEdgeNode(to); // 从from指向to
    EdgeNode *edge2 = newEdgeNode(from); // 从to指向from
    int flag = 0;

    for (int num = 0; num < g -> vertexCount; num++)
    {
        if (g -> vertices[num].data == from)
        {
            insetordered(&(g -> vertices[num].first), edge1);
            flag++;
        }

        if (g -> vertices[num].data == to)
        {
            insetordered(&(g -> vertices[num].first), edge2);
            flag++;
        }
    }

    if (flag == 2)
        return 1;
    else
        return 0;
}

void visitVertex(ALGraph *g, int v)
{
    printf("%d ", g -> vertices[v].data);
}

void DFSUtil(ALGraph *g, int v, int visited[])
{
    EdgeNode *p;
    visited[v] = 1;
    visitVertex(g, v);

    for (p = g -> vertices[v].first; p != NULL; p = p -> next)
    {
        if (visited[p -> adjvex] == 0)
        {
            DFSUtil(g, p -> adjvex, visited);
        }
    }
    visited[v] = 0;
}

void travelDFS(ALGraph *g)
{
    int visited[SIZE] = {0};
    int i;

    for (i = 0; i < g -> vertexCount; i++)
    {
        if (visited[i] == 0)
        {
            DFSUtil(g, i, visited);
        }
    }
    
    printf("\n");
}

void insetordered(EdgeNode **head, EdgeNode *node)
{
    EdgeNode *p = *head;
    EdgeNode *pre = NULL;

    while (p != NULL && p -> adjvex <= node -> adjvex)
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

void initQueue(Queue *q)
{
    q -> front = 0;
    q -> rear = 0;
}

int isQueueEmpty(Queue *q)
{
    if (q -> rear == q -> front)
        return 1;
    else 
        return 0;
}

void enQueue(Queue *q, int x)
{
    q -> data[q -> rear] = x;
    q -> rear = (q -> rear + 1) % SIZE;

}

int deQueue(Queue *q, int *x)
{
    if (isQueueEmpty(q))
        return 0;

    *x = q -> data[q -> front];
    q -> front = (q -> front + 1) % SIZE;

    return 1;
}

void BFSUtil(ALGraph *g, int start, int visited[])
{
    Queue q;
    int v;
    EdgeNode *p;

    initQueue(&q);
    visited[start] = 1;
    visitVertex(g, start);
    enQueue(&q, start);

    while (isQueueEmpty(&q) == 0)
    {
        deQueue(&q, &v);
        for (p = g -> vertices[v].first; p != NULL; p = p -> next)
        {
            if (visited[p -> adjvex] == 0)
            {
                visited[p -> adjvex] = 1;
                visitVertex(g, p -> adjvex);
                enQueue(&q, p -> adjvex);
            }
        }
    }
}

void travelBFS(ALGraph *g)
{
    int visited[SIZE] = {0};
    int i;

    for (i = 0; i < g -> vertexCount; i++)
    {
        if (visited[i] == 0)
        {
            BFSUtil(g, i, visited);
        }
    }
    printf("\n");
}

void RemoveVertex(ALGraph *g, int index)
{
    EdgeNode *p = g -> vertices[index].first;
    for (int i = 0; i < g -> vertexCount - 1; i++)
    {
        if (i >= index)
        {
            g -> vertices[i].data = g -> vertices[i + 1].data;
            g -> vertices[i].first = g -> vertices[i + 1].first;
        }

        EdgeNode *temp = g -> vertices[i].first;
        EdgeNode *pre = NULL;

        while (temp != NULL)
        {
            if (temp -> adjvex == index)
            {
                if (pre == NULL)
                {
                    g -> vertices[i].first = temp -> next;
                }
                else
                    pre -> next = temp -> next;
                g -> edgeCount--;
            }

            if (temp -> adjvex >= index)
                temp -> adjvex--;

            pre = temp;
            temp = temp -> next;
        }
    }

    g -> vertexCount--;

    free(p);


}

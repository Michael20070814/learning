#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define SIZE 500

typedef struct
{
    int id;
    int u;
    int v;
    int w;
} Edge;

void init(int n); // 对parent进行初始化 / 对rank同样进行初始化
int find(int x); // 压缩路径
int unite(int x, int y); // 按秩进行合并 若返回0则表示会形成环
int cmp(const void *a, const void *b); // qsort比较函数
int kruskal(Edge edges[], int E, int V, int *result, int *result_size); // 计算最小生成树 同时生成对应的最小权重
int cmp2(const void *a, const void *b); // 用于最后调整顺序输出

int parent[SIZE];
int rank[SIZE];

int main(void)
{
    int vertexCount;
    int edgeCount;

    scanf("%d%d", &vertexCount, &edgeCount);

    init(vertexCount);

    Edge input[edgeCount];

    for (int num = 0; num < edgeCount; num++)
    {
        scanf("%d%d%d%d", &input[num].id, &input[num].u,
            &input[num].v, &input[num].w); // 完成边的读取
    }

    int length = 0;
    int result[SIZE];

    int price = kruskal(input, edgeCount, vertexCount, result, &length);

    printf("%d\n", price);

    qsort(result, length, sizeof(int), cmp2);

    for (int num = 0; num < length; num++)
    {
        printf("%d ", result[num]);
    }

    return 0;
}

void init(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    
    return parent[x];
}

int unite(int x, int y)
{
    int px = find(x); // 找到根
    int py = find(y);
    
    if (px == py)
        return 0;

    if (rank[px] < rank[py])
        parent[px] = py;
    else if (rank[px] > rank[py])
        parent[py] = px;
    else
    {    
        rank[px]++; // 根节点变大
        parent[py] = px;
    }

    return 1;
}

int cmp(const void *a, const void *b)
{
    Edge *q = (Edge *) a;
    Edge *p = (Edge *) b;

    if (q -> w > p -> w)
        return 1;
    else if (q -> w < p -> w)
        return -1;
    else if (q -> id < p -> id)
        return -1;
    else if (q -> id > p -> id)
        return 1;
    else
        return 0;
}

int kruskal(Edge edges[], int E, int V, int *result, int *result_size)
{
    qsort(edges, E, sizeof(Edge), cmp);

    int total = 0;
    

    for (int i = 0; i < E && *result_size < V + 2; i++)
    {
        int u = edges[i].u; int v = edges[i].v; int w = edges[i].w;

        if (unite(u, v)) // 查看u和v的根节点是否相等
        {
            result[(*result_size)++] = edges[i].id;
            total += w;
        }
    }

    return total;
}


int cmp2(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;

    if (*p < *q)
        return -1;
    else if (*p > *q)
        return 1;
    else
        return 0;
}
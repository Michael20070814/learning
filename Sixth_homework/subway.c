#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define SIZE 500
#define LENGTH 100

typedef struct EdgeNode
{
    int to; // 目的地
    int line; // 线路编号
    struct EdgeNode *next; // 下一条边
} EdgeNode ;

typedef struct
{
    char name[LENGTH]; // 站的名字
    EdgeNode *first; // 第一条边
} Vertex;

Vertex Graph[SIZE];
int vertexCount = 0;

int ExtractIndex(char *name); // 根据地铁站名提取对应的序号
void AddEdge(int u, int v, int line); // 在两个站点中插入路径
void InputSubway(); // 读入地铁数据
void dijkstra(int start, int end, int prevVertex[], int prevLine[]); // Dijkstra算法找出最短路径
void PrintPath(int start, int end, int prevVertex[], int prevLine[]); // 打印最短路径

int main(void)
{
    InputSubway();

    char start[LENGTH];
    char end[LENGTH];

    scanf("%s", start);
    scanf("%s", end);

    int startindex = ExtractIndex(start);
    int endindex = ExtractIndex(end);

    int prevVertex[SIZE];
    int prevLine[SIZE];

    dijkstra(startindex, endindex, prevVertex, prevLine);

    PrintPath(startindex, endindex, prevVertex, prevLine);

    return 0;
}

int ExtractIndex(char *name)
{
    for (int i = 0; i < vertexCount; i++)
    {
        if (strcmp(Graph[i].name, name) == 0)
            return i;
    }

    vertexCount++;

    return vertexCount - 1;
}

void AddEdge(int u, int v, int line)
{
    EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode)); // 创建节点
    EdgeNode *q = (EdgeNode *)malloc(sizeof(EdgeNode));

    p -> to = v;
    q -> to = u;

    p -> line = q -> line = line;

    p -> next = q -> next = NULL;

    p -> next = Graph[u].first;
    Graph[u].first = p;

    q -> next = Graph[v].first;
    Graph[v].first = q;

}

void InputSubway()
{
    FILE *fp = fopen("bgstations.txt", "r");

    int LineNum; int LineIndex; int StationNum;

    fscanf(fp, "%d", &LineNum);

    for (int i = 0; i < LineNum; i++)
    {
        fscanf(fp, "%d%d", &LineIndex, &StationNum); // 读取地铁线路

        int prev = -1; // 预防前一站

        for (int m = 0; m < StationNum; m++) // 读取地铁站
        {
            char buffer[LENGTH]; int rubbish;

            fscanf(fp, "%s%d", buffer, &rubbish);

            int index = ExtractIndex(buffer);

            if (index == vertexCount - 1)
            {
                strcpy(Graph[index].name, buffer);
            }

            if (prev == -1)
            {
                prev = index;
                continue;
            }

            AddEdge(prev, index, LineIndex);

            prev = index;
        }
    }

    fclose(fp);
}

void dijkstra(int start, int end, int prevVertex[], int prevLine[])
{
    int dist[SIZE];
    int visited[SIZE];

    for (int i = 0; i < vertexCount; i++)
    {
        dist[i] = INFINITY;
        visited[i] = 0;
        prevVertex[i] = -1;
        prevLine[i] = -1;
    }

    dist[start] = 0;

    for (int i = 0; i < vertexCount; i++)
    {
        int u = -1;
        int min = INFINITY;

        // 找出最近的点 包括自己
        for (int j = 0; j < vertexCount; j++)
        {
            if (!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break; // 全不可达 访问完毕

        visited[u] = 1;

        if (u == end)
            break; // 访问到终点结束

        EdgeNode *p = Graph[u].first;

        while (p != NULL)
        {
            if (!visited[p -> to] && dist[u] + 1 < dist[p -> to])
            {
                dist[p -> to] = dist[u] + 1;
                prevLine[p -> to] = p -> line;
                prevVertex[p -> to] = u;
            }

            p = p -> next;
        }
    }
}

void PrintPath(int start, int end, int prevVertex[], int prevLine[])
{
    int path[SIZE];
    int count = 0;

    int cur = end;

    while (1)
    {
        path[count++] = cur;

        if (cur == start)
            break;

        cur = prevVertex[cur]; // 回溯
    }

    for (int i = 0; i < count / 2; i++)
    {
        int temp;
        temp = path[i];
        path[i] = path[count - 1 - i];
        path[count - i - 1] = temp;
    } // 排成正常顺序

    printf("%s", Graph[path[0]].name);

    int currentLine = prevLine[path[1]];
    int segmentStart = 0;

    for (int i = 1; i < count - 1; i++)
    {
        int nextLine = prevLine[path[i + 1]]; // 查看下一站路线

        if (nextLine != currentLine)
        {
            int ride = i - segmentStart;

            printf("-%d(%d)-%s", currentLine, ride, Graph[path[i]].name);

            segmentStart = i;
            currentLine = nextLine;
        }
    }

    int ride = count - 1 - segmentStart;

    printf("-%d(%d)-%s", currentLine, ride, Graph[path[count - 1]].name);
}
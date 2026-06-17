#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXV 1000
#define MAXNAME 100
#define INF 0x3f3f3f3f

typedef struct EdgeNode
{
    int to;                 // 这条边到达的站点编号
    int line;               // 这条边所属线路号
    int weight;             // 边权，这里恒为 1
    struct EdgeNode *next;
} EdgeNode;

typedef struct
{
    char name[MAXNAME];     // 站名
    EdgeNode *first;        // 邻接表头指针
} Vertex;

Vertex graph[MAXV];
int vertexCount = 0;

/* 根据站名查找编号，如果不存在则新建 */
int getVertexId(char name[])
{
    for (int i = 0; i < vertexCount; i++)
    {
        if (strcmp(graph[i].name, name) == 0)
            return i;
    }

    strcpy(graph[vertexCount].name, name);
    graph[vertexCount].first = NULL;
    vertexCount++;

    return vertexCount - 1;
}

/* 判断是否已经存在同一条线路上的同一条边，防止重复插入太多 */
int edgeExists(int from, int to, int line)
{
    EdgeNode *p = graph[from].first;

    while (p != NULL)
    {
        if (p->to == to && p->line == line)
            return 1;

        p = p->next;
    }

    return 0;
}

/* 插入一条有向边 */
void addOneEdge(int from, int to, int line)
{
    if (from == to)
        return;

    if (edgeExists(from, to, line))
        return;

    EdgeNode *node = (EdgeNode *)malloc(sizeof(EdgeNode));
    node->to = to;
    node->line = line;
    node->weight = 1;
    node->next = graph[from].first;
    graph[from].first = node;
}

/* 地铁线路是无向的，所以插入两条边 */
void addEdge(int u, int v, int line)
{
    addOneEdge(u, v, line);
    addOneEdge(v, u, line);
}

/* 读取 bgstations.txt 并建图 */
void readSubwayFile()
{
    FILE *fp = fopen("bgstations.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open bgstations.txt\n");
        exit(1);
    }

    int lineCount;
    fscanf(fp, "%d", &lineCount);

    for (int i = 0; i < lineCount; i++)
    {
        int lineNo, stationCount;
        fscanf(fp, "%d%d", &lineNo, &stationCount);

        int prev = -1;

        for (int j = 0; j < stationCount; j++)
        {
            char stationName[MAXNAME];
            int transferState;

            fscanf(fp, "%s%d", stationName, &transferState);

            int cur = getVertexId(stationName);

            if (prev != -1)
            {
                addEdge(prev, cur, lineNo);
            }

            prev = cur;
        }
    }

    fclose(fp);
}

/* Dijkstra 算法 */
void dijkstra(int start, int end, int prevVertex[], int prevLine[])
{
    int dist[MAXV];
    int visited[MAXV];

    for (int i = 0; i < vertexCount; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        prevVertex[i] = -1;
        prevLine[i] = -1;
    }

    dist[start] = 0;

    for (int i = 0; i < vertexCount; i++)
    {
        int u = -1;
        int minDist = INF;

        for (int j = 0; j < vertexCount; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        if (u == end)
            break;

        EdgeNode *p = graph[u].first;

        while (p != NULL)
        {
            int v = p->to;

            if (!visited[v] && dist[u] + p->weight < dist[v])
            {
                dist[v] = dist[u] + p->weight;
                prevVertex[v] = u;
                prevLine[v] = p->line;
            }

            p = p->next;
        }
    }
}

/* 输出压缩后的换乘线路 */
void printPath(int start, int end, int prevVertex[], int prevLine[])
{
    int path[MAXV];
    int count = 0;

    int cur = end;

    while (cur != -1)
    {
        path[count++] = cur;

        if (cur == start)
            break;

        cur = prevVertex[cur];
    }

    if (path[count - 1] != start)
    {
        printf("No path\n");
        return;
    }

    // 反转路径，使其从 start 到 end
    for (int i = 0; i < count / 2; i++)
    {
        int temp = path[i];
        path[i] = path[count - 1 - i];
        path[count - 1 - i] = temp;
    }

    if (count == 1)
    {
        printf("%s\n", graph[start].name);
        return;
    }

    printf("%s", graph[path[0]].name);

    int currentLine = prevLine[path[1]];
    int segmentStart = 0;

    for (int i = 1; i < count - 1; i++)
    {
        int nextLine = prevLine[path[i + 1]];

        if (nextLine != currentLine)
        {
            int rideStations = i - segmentStart;

            printf("-%d(%d)-%s",
                   currentLine,
                   rideStations,
                   graph[path[i]].name);

            currentLine = nextLine;
            segmentStart = i;
        }
    }

    int rideStations = count - 1 - segmentStart;

    printf("-%d(%d)-%s\n",
           currentLine,
           rideStations,
           graph[path[count - 1]].name);
}

int findStation(char name[])
{
    for (int i = 0; i < vertexCount; i++)
    {
        if (strcmp(graph[i].name, name) == 0)
            return i;
    }

    return -1;
}

int main(void)
{
    readSubwayFile();

    char startName[MAXNAME];
    char endName[MAXNAME];

    scanf("%s", startName);
    scanf("%s", endName);

    int start = findStation(startName);
    int end = findStation(endName);

    if (start == -1 || end == -1)
    {
        printf("No path\n");
        return 0;
    }

    int prevVertex[MAXV];
    int prevLine[MAXV];

    dijkstra(start, end, prevVertex, prevLine);

    printPath(start, end, prevVertex, prevLine);

    return 0;
}
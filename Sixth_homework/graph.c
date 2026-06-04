/*
 * graph.c
 *
 * Cleaned and extended graph code based on the course materials about graphs:
 * adjacency matrix, adjacency list, DFS, BFS, minimum spanning tree, and shortest paths.
 *
 * All vertex indexes in this file are 0-based: 0, 1, ..., vertexCount - 1.
 * The code is written as a reusable study template. You may copy individual functions
 * into homework answers according to the required input/output format.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXV 512
#define INF 1000000000

/* ============================================================
 * Basic data structures
 * ============================================================ */

typedef enum {
    UNDIRECTED = 0,
    DIRECTED = 1
} GraphKind;

/* Edge node in an adjacency list. */
typedef struct EdgeNode {
    int edgeId;                 /* Optional edge number, useful for path output. */
    int adjvex;                 /* Index of the adjacent vertex. */
    int weight;                 /* Edge weight. Use 1 for an unweighted graph. */
    struct EdgeNode *next;      /* Next edge from the same start vertex. */
} EdgeNode;

/* Vertex head node in an adjacency list. */
typedef struct VertexNode {
    int data;                   /* Vertex data. Here we simply store an integer label. */
    EdgeNode *first;            /* First outgoing edge. */
} VertexNode;

/* Adjacency-list graph. */
typedef struct {
    VertexNode vertices[MAXV];
    int vertexCount;
    int edgeCount;
    GraphKind kind;
} ALGraph;

/* Adjacency-matrix graph. */
typedef struct {
    int vertex[MAXV];           /* Vertex labels. */
    int weight[MAXV][MAXV];     /* Matrix value: INF means no edge, 0 on diagonal. */
    int vertexCount;
    int edgeCount;
    GraphKind kind;
} MGraph;

/* Simple circular queue for BFS. */
typedef struct {
    int data[MAXV];
    int front;
    int rear;
} Queue;

/* Edge item for Kruskal's algorithm. */
typedef struct {
    int u;
    int v;
    int w;
} EdgeItem;

/* ============================================================
 * Queue utilities
 * ============================================================ */

static void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

static int isQueueEmpty(const Queue *q) {
    return q->front == q->rear;
}

static int enqueue(Queue *q, int x) {
    int nextRear = (q->rear + 1) % MAXV;
    if (nextRear == q->front) {
        return 0;               /* Queue is full. */
    }
    q->data[q->rear] = x;
    q->rear = nextRear;
    return 1;
}

static int dequeue(Queue *q, int *x) {
    if (isQueueEmpty(q)) {
        return 0;
    }
    *x = q->data[q->front];
    q->front = (q->front + 1) % MAXV;
    return 1;
}

/* ============================================================
 * Adjacency-list graph: creation, insertion, deletion, destroy
 * ============================================================ */

void initALGraph(ALGraph *g, int vertexCount, GraphKind kind) {
    int i;
    if (vertexCount < 0 || vertexCount > MAXV) {
        fprintf(stderr, "Invalid vertex count.\n");
        exit(EXIT_FAILURE);
    }

    g->vertexCount = vertexCount;
    g->edgeCount = 0;
    g->kind = kind;

    for (i = 0; i < vertexCount; i++) {
        g->vertices[i].data = i;
        g->vertices[i].first = NULL;
    }
}

static EdgeNode *newEdgeNode(int adjvex, int weight, int edgeId) {
    EdgeNode *node = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (node == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    node->edgeId = edgeId;
    node->adjvex = adjvex;
    node->weight = weight;
    node->next = NULL;
    return node;
}

/* Insert one directed edge into the head of a linked list. */
static void insertArcAL(ALGraph *g, int from, int to, int weight, int edgeId) {
    EdgeNode *node = newEdgeNode(to, weight, edgeId);
    node->next = g->vertices[from].first;
    g->vertices[from].first = node;
}

/* Insert an edge. For an undirected graph, insert two opposite arcs. */
int insertEdgeAL(ALGraph *g, int from, int to, int weight, int edgeId) {
    if (from < 0 || from >= g->vertexCount || to < 0 || to >= g->vertexCount) {
        return 0;
    }

    insertArcAL(g, from, to, weight, edgeId);
    if (g->kind == UNDIRECTED && from != to) {
        insertArcAL(g, to, from, weight, edgeId);
    }
    g->edgeCount++;
    return 1;
}

/* Create an adjacency-list graph from standard input.
 * Input format:
 *   n m directedFlag
 *   u v w
 *   u v w
 *   ... m lines
 * directedFlag: 0 means undirected, 1 means directed.
 */
int createALGraphFromInput(ALGraph *g) {
    int n, m, directedFlag;
    int i, u, v, w;

    if (scanf("%d %d %d", &n, &m, &directedFlag) != 3) {
        return 0;
    }
    initALGraph(g, n, directedFlag ? DIRECTED : UNDIRECTED);

    for (i = 0; i < m; i++) {
        if (scanf("%d %d %d", &u, &v, &w) != 3) {
            return 0;
        }
        insertEdgeAL(g, u, v, w, i);
    }
    return 1;
}

static int deleteArcAL(ALGraph *g, int from, int to) {
    EdgeNode *p;
    EdgeNode *prev;

    if (from < 0 || from >= g->vertexCount) {
        return 0;
    }

    p = g->vertices[from].first;
    prev = NULL;
    while (p != NULL) {
        if (p->adjvex == to) {
            if (prev == NULL) {
                g->vertices[from].first = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            return 1;
        }
        prev = p;
        p = p->next;
    }
    return 0;
}

int deleteEdgeAL(ALGraph *g, int from, int to) {
    int removed = deleteArcAL(g, from, to);
    if (g->kind == UNDIRECTED && from != to) {
        deleteArcAL(g, to, from);
    }
    if (removed) {
        g->edgeCount--;
    }
    return removed;
}

void destroyALGraph(ALGraph *g) {
    int i;
    for (i = 0; i < g->vertexCount; i++) {
        EdgeNode *p = g->vertices[i].first;
        while (p != NULL) {
            EdgeNode *next = p->next;
            free(p);
            p = next;
        }
        g->vertices[i].first = NULL;
    }
    g->vertexCount = 0;
    g->edgeCount = 0;
}

void printALGraph(const ALGraph *g) {
    int i;
    for (i = 0; i < g->vertexCount; i++) {
        EdgeNode *p = g->vertices[i].first;
        printf("%d:", i);
        while (p != NULL) {
            printf(" -> %d(w=%d,id=%d)", p->adjvex, p->weight, p->edgeId);
            p = p->next;
        }
        printf("\n");
    }
}

/* ============================================================
 * Adjacency-matrix graph: creation and conversion
 * ============================================================ */

void initMGraph(MGraph *g, int vertexCount, GraphKind kind) {
    int i, j;
    if (vertexCount < 0 || vertexCount > MAXV) {
        fprintf(stderr, "Invalid vertex count.\n");
        exit(EXIT_FAILURE);
    }

    g->vertexCount = vertexCount;
    g->edgeCount = 0;
    g->kind = kind;

    for (i = 0; i < vertexCount; i++) {
        g->vertex[i] = i;
        for (j = 0; j < vertexCount; j++) {
            g->weight[i][j] = (i == j) ? 0 : INF;
        }
    }
}

int insertEdgeM(MGraph *g, int from, int to, int weight) {
    if (from < 0 || from >= g->vertexCount || to < 0 || to >= g->vertexCount) {
        return 0;
    }
    if (g->weight[from][to] == INF) {
        g->edgeCount++;
    }
    g->weight[from][to] = weight;
    if (g->kind == UNDIRECTED) {
        g->weight[to][from] = weight;
    }
    return 1;
}

int deleteEdgeM(MGraph *g, int from, int to) {
    if (from < 0 || from >= g->vertexCount || to < 0 || to >= g->vertexCount) {
        return 0;
    }
    if (g->weight[from][to] == INF) {
        return 0;
    }
    g->weight[from][to] = INF;
    if (g->kind == UNDIRECTED) {
        g->weight[to][from] = INF;
    }
    g->edgeCount--;
    return 1;
}

void matrixToList(const MGraph *mg, ALGraph *lg) {
    int i, j, edgeId = 0;
    initALGraph(lg, mg->vertexCount, mg->kind);
    for (i = 0; i < mg->vertexCount; i++) {
        lg->vertices[i].data = mg->vertex[i];
    }

    for (i = 0; i < mg->vertexCount; i++) {
        for (j = 0; j < mg->vertexCount; j++) {
            if (i != j && mg->weight[i][j] != INF) {
                if (mg->kind == DIRECTED || i < j) {
                    insertEdgeAL(lg, i, j, mg->weight[i][j], edgeId++);
                }
            }
        }
    }
}

void listToMatrix(const ALGraph *lg, MGraph *mg) {
    int i;
    initMGraph(mg, lg->vertexCount, lg->kind);
    for (i = 0; i < lg->vertexCount; i++) {
        EdgeNode *p = lg->vertices[i].first;
        mg->vertex[i] = lg->vertices[i].data;
        while (p != NULL) {
            insertEdgeM(mg, i, p->adjvex, p->weight);
            p = p->next;
        }
    }
}

void printMGraph(const MGraph *g) {
    int i, j;
    for (i = 0; i < g->vertexCount; i++) {
        for (j = 0; j < g->vertexCount; j++) {
            if (g->weight[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%3d ", g->weight[i][j]);
            }
        }
        printf("\n");
    }
}

/* ============================================================
 * Graph traversal: DFS and BFS
 * ============================================================ */

static void visitVertex(const ALGraph *g, int v) {
    printf("%d ", g->vertices[v].data);
}

static void DFSUtil(const ALGraph *g, int v, int visited[]) {
    EdgeNode *p;
    visited[v] = 1;
    visitVertex(g, v);

    for (p = g->vertices[v].first; p != NULL; p = p->next) {
        if (!visited[p->adjvex]) {
            DFSUtil(g, p->adjvex, visited);
        }
    }
}

/* Traverse all connected components by depth first search. */
void travelDFS(const ALGraph *g) {
    int visited[MAXV] = {0};
    int i;

    for (i = 0; i < g->vertexCount; i++) {
        if (!visited[i]) {
            DFSUtil(g, i, visited);
        }
    }
    printf("\n");
}

static void BFSUtil(const ALGraph *g, int start, int visited[]) {
    Queue q;
    int v;
    EdgeNode *p;

    initQueue(&q);
    visited[start] = 1;
    visitVertex(g, start);
    enqueue(&q, start);

    while (!isQueueEmpty(&q)) {
        dequeue(&q, &v);
        for (p = g->vertices[v].first; p != NULL; p = p->next) {
            if (!visited[p->adjvex]) {
                visited[p->adjvex] = 1;
                visitVertex(g, p->adjvex);
                enqueue(&q, p->adjvex);
            }
        }
    }
}

/* Traverse all connected components by breadth first search. */
void travelBFS(const ALGraph *g) {
    int visited[MAXV] = {0};
    int i;

    for (i = 0; i < g->vertexCount; i++) {
        if (!visited[i]) {
            BFSUtil(g, i, visited);
        }
    }
    printf("\n");
}

/* ============================================================
 * Basic graph queries
 * ============================================================ */

int outDegreeAL(const ALGraph *g, int v) {
    int degree = 0;
    EdgeNode *p;

    if (v < 0 || v >= g->vertexCount) {
        return -1;
    }
    for (p = g->vertices[v].first; p != NULL; p = p->next) {
        degree++;
    }
    return degree;
}

int inDegreeAL(const ALGraph *g, int v) {
    int i, degree = 0;
    if (v < 0 || v >= g->vertexCount) {
        return -1;
    }

    for (i = 0; i < g->vertexCount; i++) {
        EdgeNode *p = g->vertices[i].first;
        while (p != NULL) {
            if (p->adjvex == v) {
                degree++;
            }
            p = p->next;
        }
    }
    return degree;
}

int isConnectedUndirected(const ALGraph *g) {
    int visited[MAXV] = {0};
    int i;

    if (g->vertexCount == 0) {
        return 1;
    }
    DFSUtil(g, 0, visited);
    printf("\n");

    for (i = 0; i < g->vertexCount; i++) {
        if (!visited[i]) {
            return 0;
        }
    }
    return 1;
}

/* ============================================================
 * Minimum spanning tree: Prim and Kruskal
 * ============================================================ */

/* Prim's algorithm for an undirected weighted graph stored by adjacency matrix.
 * parent[i] stores the predecessor of vertex i in the MST.
 * Return the total weight, or INF if the graph is disconnected.
 */
int primMST(const MGraph *g, int start, int parent[]) {
    int lowCost[MAXV];
    int selected[MAXV] = {0};
    int i, j, k;
    int total = 0;

    if (start < 0 || start >= g->vertexCount) {
        return INF;
    }

    for (i = 0; i < g->vertexCount; i++) {
        lowCost[i] = g->weight[start][i];
        parent[i] = (g->weight[start][i] < INF && i != start) ? start : -1;
    }

    selected[start] = 1;
    lowCost[start] = 0;
    parent[start] = -1;

    for (i = 1; i < g->vertexCount; i++) {
        int minCost = INF;
        k = -1;

        for (j = 0; j < g->vertexCount; j++) {
            if (!selected[j] && lowCost[j] < minCost) {
                minCost = lowCost[j];
                k = j;
            }
        }

        if (k == -1) {
            return INF;          /* Disconnected graph. */
        }

        selected[k] = 1;
        total += minCost;

        for (j = 0; j < g->vertexCount; j++) {
            if (!selected[j] && g->weight[k][j] < lowCost[j]) {
                lowCost[j] = g->weight[k][j];
                parent[j] = k;
            }
        }
    }

    return total;
}

static int compareEdgeItem(const void *a, const void *b) {
    const EdgeItem *ea = (const EdgeItem *)a;
    const EdgeItem *eb = (const EdgeItem *)b;
    return ea->w - eb->w;
}

static int dsuFind(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = dsuFind(parent, parent[x]);
    }
    return parent[x];
}

static int dsuUnion(int parent[], int rank[], int a, int b) {
    int ra = dsuFind(parent, a);
    int rb = dsuFind(parent, b);

    if (ra == rb) {
        return 0;
    }
    if (rank[ra] < rank[rb]) {
        parent[ra] = rb;
    } else if (rank[ra] > rank[rb]) {
        parent[rb] = ra;
    } else {
        parent[rb] = ra;
        rank[ra]++;
    }
    return 1;
}

/* Kruskal's algorithm for an undirected weighted graph stored by adjacency matrix.
 * resultEdges receives the selected MST edges.
 * resultCount receives the number of selected edges.
 * Return total weight, or INF if the graph is disconnected.
 */
int kruskalMST(const MGraph *g, EdgeItem resultEdges[], int *resultCount) {
    EdgeItem edges[MAXV * MAXV / 2];
    int edgeCount = 0;
    int parent[MAXV];
    int rank[MAXV] = {0};
    int i, j;
    int total = 0;

    *resultCount = 0;

    for (i = 0; i < g->vertexCount; i++) {
        for (j = i + 1; j < g->vertexCount; j++) {
            if (g->weight[i][j] != INF) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].w = g->weight[i][j];
                edgeCount++;
            }
        }
    }

    qsort(edges, edgeCount, sizeof(EdgeItem), compareEdgeItem);

    for (i = 0; i < g->vertexCount; i++) {
        parent[i] = i;
    }

    for (i = 0; i < edgeCount && *resultCount < g->vertexCount - 1; i++) {
        if (dsuUnion(parent, rank, edges[i].u, edges[i].v)) {
            resultEdges[*resultCount] = edges[i];
            (*resultCount)++;
            total += edges[i].w;
        }
    }

    if (*resultCount != g->vertexCount - 1) {
        return INF;
    }
    return total;
}

/* ============================================================
 * Shortest paths: Dijkstra and Floyd-Warshall
 * ============================================================ */

/* Dijkstra's algorithm for a graph with non-negative edge weights.
 * dist[i] is the shortest distance from source to i.
 * path[i] is the direct predecessor of i on the shortest path.
 */
void dijkstra(const MGraph *g, int source, int dist[], int path[]) {
    int selected[MAXV] = {0};
    int i, j, v;

    for (i = 0; i < g->vertexCount; i++) {
        dist[i] = g->weight[source][i];
        path[i] = (g->weight[source][i] < INF && i != source) ? source : -1;
    }

    dist[source] = 0;
    path[source] = -1;
    selected[source] = 1;

    for (i = 1; i < g->vertexCount; i++) {
        int minDist = INF;
        v = -1;

        for (j = 0; j < g->vertexCount; j++) {
            if (!selected[j] && dist[j] < minDist) {
                minDist = dist[j];
                v = j;
            }
        }

        if (v == -1) {
            break;              /* Remaining vertices are unreachable. */
        }

        selected[v] = 1;

        for (j = 0; j < g->vertexCount; j++) {
            if (!selected[j] && g->weight[v][j] != INF && dist[v] + g->weight[v][j] < dist[j]) {
                dist[j] = dist[v] + g->weight[v][j];
                path[j] = v;
            }
        }
    }
}

static void printPathRecursive(int path[], int source, int target) {
    if (target == source) {
        printf("%d", source);
        return;
    }
    if (path[target] == -1) {
        printf("unreachable");
        return;
    }
    printPathRecursive(path, source, path[target]);
    printf(" -> %d", target);
}

void printDijkstraResult(const MGraph *g, int source, int dist[], int path[]) {
    int i;
    for (i = 0; i < g->vertexCount; i++) {
        printf("%d to %d: ", source, i);
        if (dist[i] == INF) {
            printf("unreachable\n");
        } else {
            printf("distance=%d, path=", dist[i]);
            printPathRecursive(path, source, i);
            printf("\n");
        }
    }
}

/* Floyd-Warshall algorithm for all-pairs shortest paths.
 * dist[i][j] is the shortest distance from i to j.
 * next[i][j] stores the next vertex after i when walking to j.
 */
void floydWarshall(const MGraph *g, int dist[MAXV][MAXV], int next[MAXV][MAXV]) {
    int i, j, k;

    for (i = 0; i < g->vertexCount; i++) {
        for (j = 0; j < g->vertexCount; j++) {
            dist[i][j] = g->weight[i][j];
            if (i != j && g->weight[i][j] != INF) {
                next[i][j] = j;
            } else {
                next[i][j] = -1;
            }
        }
    }

    for (k = 0; k < g->vertexCount; k++) {
        for (i = 0; i < g->vertexCount; i++) {
            for (j = 0; j < g->vertexCount; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printFloydPath(int next[MAXV][MAXV], int from, int to) {
    int current = from;
    if (next[from][to] == -1) {
        printf("unreachable");
        return;
    }

    printf("%d", current);
    while (current != to) {
        current = next[current][to];
        printf(" -> %d", current);
    }
}

/* ============================================================
 * Extended algorithms
 * ============================================================ */

/* Topological sort for a directed acyclic graph.
 * order receives the topological order.
 * Return 1 if successful, or 0 if the graph has a cycle.
 */
int topologicalSort(const ALGraph *g, int order[]) {
    int indegree[MAXV] = {0};
    Queue q;
    int i, v, count = 0;

    for (i = 0; i < g->vertexCount; i++) {
        EdgeNode *p = g->vertices[i].first;
        while (p != NULL) {
            indegree[p->adjvex]++;
            p = p->next;
        }
    }

    initQueue(&q);
    for (i = 0; i < g->vertexCount; i++) {
        if (indegree[i] == 0) {
            enqueue(&q, i);
        }
    }

    while (!isQueueEmpty(&q)) {
        EdgeNode *p;
        dequeue(&q, &v);
        order[count++] = v;

        for (p = g->vertices[v].first; p != NULL; p = p->next) {
            indegree[p->adjvex]--;
            if (indegree[p->adjvex] == 0) {
                enqueue(&q, p->adjvex);
            }
        }
    }

    return count == g->vertexCount;
}

static int hasCycleUndirectedDFS(const ALGraph *g, int v, int parent, int visited[]) {
    EdgeNode *p;
    visited[v] = 1;

    for (p = g->vertices[v].first; p != NULL; p = p->next) {
        int to = p->adjvex;
        if (!visited[to]) {
            if (hasCycleUndirectedDFS(g, to, v, visited)) {
                return 1;
            }
        } else if (to != parent) {
            return 1;
        }
    }
    return 0;
}

int hasCycleUndirected(const ALGraph *g) {
    int visited[MAXV] = {0};
    int i;

    for (i = 0; i < g->vertexCount; i++) {
        if (!visited[i] && hasCycleUndirectedDFS(g, i, -1, visited)) {
            return 1;
        }
    }
    return 0;
}

/* Print all simple paths from source to target using vertex numbers. */
static void printAllPathsDFS(const ALGraph *g, int v, int target, int visited[], int path[], int depth) {
    EdgeNode *p;
    visited[v] = 1;
    path[depth] = v;

    if (v == target) {
        int i;
        for (i = 0; i <= depth; i++) {
            printf("%d%c", path[i], (i == depth) ? '\n' : ' ');
        }
    } else {
        for (p = g->vertices[v].first; p != NULL; p = p->next) {
            if (!visited[p->adjvex]) {
                printAllPathsDFS(g, p->adjvex, target, visited, path, depth + 1);
            }
        }
    }

    visited[v] = 0;             /* Backtrack so the vertex may appear in another path. */
}

void printAllSimplePaths(const ALGraph *g, int source, int target) {
    int visited[MAXV] = {0};
    int path[MAXV];

    if (source < 0 || source >= g->vertexCount || target < 0 || target >= g->vertexCount) {
        return;
    }
    printAllPathsDFS(g, source, target, visited, path, 0);
}

/* Print all simple paths from source to target using edge IDs.
 * This matches homework styles where a route is represented by edge numbers.
 */
static void printAllEdgePathsDFS(const ALGraph *g, int v, int target, int visited[], int edgePath[], int depth) {
    EdgeNode *p;
    visited[v] = 1;

    if (v == target) {
        int i;
        for (i = 0; i < depth; i++) {
            printf("%d%c", edgePath[i], (i == depth - 1) ? '\n' : ' ');
        }
        if (depth == 0) {
            printf("\n");
        }
    } else {
        for (p = g->vertices[v].first; p != NULL; p = p->next) {
            if (!visited[p->adjvex]) {
                edgePath[depth] = p->edgeId;
                printAllEdgePathsDFS(g, p->adjvex, target, visited, edgePath, depth + 1);
            }
        }
    }

    visited[v] = 0;
}

void printAllSimpleEdgePaths(const ALGraph *g, int source, int target) {
    int visited[MAXV] = {0};
    int edgePath[MAXV];

    if (source < 0 || source >= g->vertexCount || target < 0 || target >= g->vertexCount) {
        return;
    }
    printAllEdgePathsDFS(g, source, target, visited, edgePath, 0);
}

/* ============================================================
 * Demonstration code
 * ============================================================ */

static void demo(void) {
    ALGraph lg;
    MGraph mg;
    int parent[MAXV];
    int dist[MAXV];
    int path[MAXV];
    EdgeItem mstEdges[MAXV];
    int mstCount = 0;
    int total;

    initMGraph(&mg, 6, UNDIRECTED);
    insertEdgeM(&mg, 0, 1, 16);
    insertEdgeM(&mg, 0, 2, 20);
    insertEdgeM(&mg, 0, 3, 19);
    insertEdgeM(&mg, 1, 2, 11);
    insertEdgeM(&mg, 1, 4, 6);
    insertEdgeM(&mg, 1, 5, 5);
    insertEdgeM(&mg, 2, 3, 22);
    insertEdgeM(&mg, 2, 4, 14);
    insertEdgeM(&mg, 3, 4, 18);
    insertEdgeM(&mg, 4, 5, 9);

    matrixToList(&mg, &lg);

    printf("Adjacency list:\n");
    printALGraph(&lg);

    printf("DFS: ");
    travelDFS(&lg);

    printf("BFS: ");
    travelBFS(&lg);

    total = primMST(&mg, 0, parent);
    printf("Prim MST total weight: %d\n", total);

    total = kruskalMST(&mg, mstEdges, &mstCount);
    printf("Kruskal MST total weight: %d\n", total);

    dijkstra(&mg, 0, dist, path);
    printf("Dijkstra from 0:\n");
    printDijkstraResult(&mg, 0, dist, path);

    printf("All simple vertex paths from 0 to 5:\n");
    printAllSimplePaths(&lg, 0, 5);

    destroyALGraph(&lg);
}

int main(void) {
    demo();
    return 0;
}

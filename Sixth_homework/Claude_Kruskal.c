#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 100
#define MAX_VERTICES 100

/* 边结构 */
typedef struct {
    int u, v, w;  /* 起点、终点、权重 */
} Edge;

/* 并查集 */
int parent[MAX_VERTICES];
int rank_[MAX_VERTICES];

void init_uf(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }
}

/* 路径压缩 */
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

/* 按秩合并，返回 0 表示已在同一集合（会成环） */
int unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return 0;          /* 同一连通分量，加入会成环 */
    if (rank_[px] < rank_[py]) { int t = px; px = py; py = t; }
    parent[py] = px;
    if (rank_[px] == rank_[py]) rank_[px]++;
    return 1;
}

/* 比较函数，供 qsort 使用 */
int cmp_edge(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

/* Kruskal 算法
 * edges[]: 所有边；E: 边数；V: 顶点数
 * mst[]:   输出 MST 的边；返回 MST 总权重 */
int kruskal(Edge edges[], int E, int V, Edge mst[], int *mst_size) {
    qsort(edges, E, sizeof(Edge), cmp_edge);  /* 按权重排序 */
    init_uf(V);

    int total = 0;
    *mst_size = 0;

    for (int i = 0; i < E && *mst_size < V - 1; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (unite(u, v)) {           /* 不成环，加入 MST */
            mst[(*mst_size)++] = edges[i];
            total += w;
        }
    }
    return total;
}

int main() {
    Edge edges[] = {
        {0,1,4},{0,3,2},{1,2,6},{1,4,5},
        {2,5,3},{3,4,8},{4,5,7},{2,4,1}
    };
    int E = 8, V = 6;
    Edge mst[MAX_VERTICES];
    int mst_size = 0;

    int total = kruskal(edges, E, V, mst, &mst_size);

    printf("最小生成树的边：\n");
    for (int i = 0; i < mst_size; i++)
        printf("  %d -- %d  权重: %d\n", mst[i].u, mst[i].v, mst[i].w);
    printf("总权重: %d\n", total);
    return 0;
}
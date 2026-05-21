// tree_graph_algorithms.c
// 数据结构第 8-10 讲配套：树、二叉树、BST、AVL、Huffman、表达式树、堆、Trie、图遍历。
// 编译：gcc -std=c11 -Wall -Wextra -pedantic tree_graph_algorithms.c -o tree_graph_algorithms

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================
// 1. 二叉树与 BST
// ============================================================

typedef struct BTNode {
    int data;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode, *BTNodeptr;

// 创建二叉查找树的节点
static BTNodeptr bt_new(int data) {
    BTNodeptr p = (BTNodeptr)malloc(sizeof(BTNode));
    if (!p) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    p->data = data;
    p->lchild = p->rchild = NULL;
    return p;
}

static void visit_int(BTNodeptr p) {
    if (p) printf("%d ", p->data);
}

// 二叉查找树节点的插入
BTNodeptr bst_insert(BTNodeptr root, int data) {
    if (root == NULL) return bt_new(data);
    if (data < root->data)
        root->lchild = bst_insert(root->lchild, data);
    else
        root->rchild = bst_insert(root->rchild, data);  // 约定：重复值放右子树
    return root;
}

BTNodeptr bst_search_iter(BTNodeptr root, int key) {
    while (root != NULL) {
        if (key == root->data) return root;
        root = (key < root->data) ? root->lchild : root->rchild;
    }
    return NULL;
}

BTNodeptr bst_search_rec(BTNodeptr root, int key) {
    if (root == NULL || root->data == key) return root;
    if (key < root->data) return bst_search_rec(root->lchild, key);
    return bst_search_rec(root->rchild, key);
}

static BTNodeptr bst_min_node(BTNodeptr root) {
    while (root && root->lchild) root = root->lchild;
    return root;
}

BTNodeptr bst_delete(BTNodeptr root, int key) {
    if (root == NULL) return NULL;
    if (key < root->data) {
        root->lchild = bst_delete(root->lchild, key);
    } else if (key > root->data) {
        root->rchild = bst_delete(root->rchild, key);
    } else {
        // 找到待删结点：0/1 个孩子直接接上；2 个孩子用右子树最小值替代。
        if (root->lchild == NULL) {
            BTNodeptr r = root->rchild;
            free(root);
            return r;
        }
        if (root->rchild == NULL) {
            BTNodeptr l = root->lchild;
            free(root);
            return l;
        }
        BTNodeptr succ = bst_min_node(root->rchild);
        root->data = succ->data;
        root->rchild = bst_delete(root->rchild, succ->data);
    }
    return root;
}

void print_bst_ancestors(BTNodeptr root, int key) {
    // 非递归：沿 BST 查找路径输出祖先。若 key 不存在，输出的是失败查找路径。
    while (root && root->data != key) {
        printf("%d ", root->data);
        root = (key < root->data) ? root->lchild : root->rchild;
    }
}

void preorder(BTNodeptr t) {
    if (t) {
        visit_int(t);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

void inorder(BTNodeptr t) {
    if (t) {
        inorder(t->lchild);
        visit_int(t);
        inorder(t->rchild);
    }
}

void postorder(BTNodeptr t) {
    if (t) {
        postorder(t->lchild);
        postorder(t->rchild);
        visit_int(t);
    }
}

#define STACK_CAP 1024
#define QUEUE_CAP 1024

void inorder_iter(BTNodeptr root) {
    BTNodeptr stack[STACK_CAP];
    int top = -1;
    BTNodeptr p = root;
    while (p != NULL || top != -1) {
        while (p != NULL) {
            stack[++top] = p;
            p = p->lchild;
        }
        p = stack[top--];
        visit_int(p);
        p = p->rchild;
    }
}

void preorder_iter(BTNodeptr root) {
    if (!root) return;
    BTNodeptr stack[STACK_CAP];
    int top = -1;
    stack[++top] = root;
    while (top != -1) {
        BTNodeptr p = stack[top--];
        visit_int(p);
        if (p->rchild) stack[++top] = p->rchild;  // 右先入栈，左先出栈
        if (p->lchild) stack[++top] = p->lchild;
    }
}

void postorder_iter(BTNodeptr root) {
    // 一个栈 + last 指针：只有右子树为空或已访问后，才能访问根。
    BTNodeptr stack[STACK_CAP];
    int top = -1;
    BTNodeptr p = root;
    BTNodeptr last = NULL;
    while (p != NULL || top != -1) {
        if (p != NULL) {
            stack[++top] = p;
            p = p->lchild;
        } else {
            BTNodeptr peek = stack[top];
            if (peek->rchild && last != peek->rchild) {
                p = peek->rchild;
            } else {
                visit_int(peek);
                last = peek;
                top--;
            }
        }
    }
}

void levelorder(BTNodeptr root) {
    if (!root) return;
    BTNodeptr q[QUEUE_CAP];
    int front = 0, rear = 0;
    q[rear++] = root;
    while (front < rear) {
        BTNodeptr p = q[front++];
        visit_int(p);
        if (p->lchild) q[rear++] = p->lchild;
        if (p->rchild) q[rear++] = p->rchild;
    }
}

int bt_height(BTNodeptr root) {
    if (!root) return 0;
    int lh = bt_height(root->lchild);
    int rh = bt_height(root->rchild);
    return 1 + (lh > rh ? lh : rh);
}

int bt_leaf_count(BTNodeptr root) {
    if (!root) return 0;
    if (!root->lchild && !root->rchild) return 1;
    return bt_leaf_count(root->lchild) + bt_leaf_count(root->rchild);
}

// 遍历叶子节点与高度 中序遍历
// 前序遍历先打印，再看左，再看右。如果需要保持左右顺序的话，需要用中序
void print_leaves_with_height(BTNodeptr root, int height) 
{
    if (!root) return;
    print_leaves_with_height(root->lchild, height + 1);

    if (!root->lchild && !root->rchild)
        printf("%d %d\n", root->data, height);

    print_leaves_with_height(root->rchild, height + 1);
}

BTNodeptr copy_tree(BTNodeptr src) {
    if (src == NULL) return NULL;
    BTNodeptr obj = bt_new(src->data);
    obj->lchild = copy_tree(src->lchild);
    obj->rchild = copy_tree(src->rchild);
    return obj;
}

void destroy_tree(BTNodeptr *root) {
    if (root == NULL || *root == NULL) return;
    destroy_tree(&((*root)->lchild));
    destroy_tree(&((*root)->rchild));
    free(*root);
    *root = NULL;
}

static int find_index(const int a[], int left, int right, int value) {
    for (int i = left; i <= right; ++i) {
        if (a[i] == value) return i;
    }
    return -1;
}

BTNodeptr build_from_pre_in(const int pre[], int pre_l, int pre_r,
                            const int in[], int in_l, int in_r) {
    if (pre_l > pre_r) return NULL;
    int root_value = pre[pre_l];
    int k = find_index(in, in_l, in_r, root_value);
    if (k < 0) return NULL;
    int left_size = k - in_l;
    BTNodeptr root = bt_new(root_value);
    root->lchild = build_from_pre_in(pre, pre_l + 1, pre_l + left_size, in, in_l, k - 1);
    root->rchild = build_from_pre_in(pre, pre_l + left_size + 1, pre_r, in, k + 1, in_r);
    return root;
}

// ============================================================
// 2. AVL 平衡二叉查找树
// ============================================================

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

static int avl_h(AVLNode *p) { return p ? p->height : 0; }
static int max_int(int a, int b) { return a > b ? a : b; }

static AVLNode *avl_new(int key) {
    AVLNode *p = (AVLNode *)malloc(sizeof(AVLNode));
    if (!p) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    p->key = key;
    p->height = 1;
    p->left = p->right = NULL;
    return p;
}

static AVLNode *right_rotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = max_int(avl_h(y->left), avl_h(y->right)) + 1;
    x->height = max_int(avl_h(x->left), avl_h(x->right)) + 1;
    return x;
}

static AVLNode *left_rotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = max_int(avl_h(x->left), avl_h(x->right)) + 1;
    y->height = max_int(avl_h(y->left), avl_h(y->right)) + 1;
    return y;
}

static int balance_factor(AVLNode *p) {
    return p ? avl_h(p->left) - avl_h(p->right) : 0;
}

AVLNode *avl_insert(AVLNode *node, int key) {
    if (node == NULL) return avl_new(key);
    if (key < node->key)
        node->left = avl_insert(node->left, key);
    else if (key > node->key)
        node->right = avl_insert(node->right, key);
    else
        return node;  // 本示例不插入重复 key

    node->height = 1 + max_int(avl_h(node->left), avl_h(node->right));
    int bf = balance_factor(node);

    // LL
    if (bf > 1 && key < node->left->key) return right_rotate(node);
    // RR
    if (bf < -1 && key > node->right->key) return left_rotate(node);
    // LR
    if (bf > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    // RL
    if (bf < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

void avl_inorder(AVLNode *root) {
    if (root) {
        avl_inorder(root->left);
        printf("%d(h=%d,bf=%d) ", root->key, root->height, balance_factor(root));
        avl_inorder(root->right);
    }
}

void avl_destroy(AVLNode *root) {
    if (!root) return;
    avl_destroy(root->left);
    avl_destroy(root->right);
    free(root);
}

// ============================================================
// 3. 大顶堆：优先队列的数组实现
// ============================================================

#define HEAP_CAP 1024

typedef struct MaxHeap {
    int a[HEAP_CAP];
    int size;
} MaxHeap;

void heap_init(MaxHeap *h) { h->size = 0; }

void heap_push(MaxHeap *h, int value) {
    if (h->size >= HEAP_CAP) {
        fprintf(stderr, "heap full\n");
        return;
    }
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->a[parent] >= value) break;
        h->a[i] = h->a[parent];
        i = parent;
    }
    h->a[i] = value;
}

int heap_pop(MaxHeap *h) {
    if (h->size == 0) {
        fprintf(stderr, "heap empty\n");
        return 0;
    }
    int top = h->a[0];
    int last = h->a[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int child = 2 * i + 1;
        if (child + 1 < h->size && h->a[child + 1] > h->a[child]) child++;
        if (last >= h->a[child]) break;
        h->a[i] = h->a[child];
        i = child;
    }
    h->a[i] = last;
    return top;
}

void heap_build(MaxHeap *h, const int a[], int n) {
    heap_init(h);
    for (int i = 0; i < n; ++i) heap_push(h, a[i]);
}

// ============================================================
// 4. Huffman 树与编码
// ============================================================

typedef struct HNode {
    unsigned char ch;
    int freq;
    struct HNode *left;
    struct HNode *right;
} HNode;

typedef struct HMinHeap {
    HNode *a[512];
    int size;
} HMinHeap;

static HNode *hnode_new(unsigned char ch, int freq, HNode *left, HNode *right) {
    HNode *p = (HNode *)malloc(sizeof(HNode));
    if (!p) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    p->ch = ch;
    p->freq = freq;
    p->left = left;
    p->right = right;
    return p;
}

static void hheap_init(HMinHeap *h) { h->size = 0; }

static void hheap_push(HMinHeap *h, HNode *node) {
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->a[parent]->freq <= node->freq) break;
        h->a[i] = h->a[parent];
        i = parent;
    }
    h->a[i] = node;
}

static HNode *hheap_pop(HMinHeap *h) {
    HNode *top = h->a[0];
    HNode *last = h->a[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int child = 2 * i + 1;
        if (child + 1 < h->size && h->a[child + 1]->freq < h->a[child]->freq) child++;
        if (last->freq <= h->a[child]->freq) break;
        h->a[i] = h->a[child];
        i = child;
    }
    if (h->size > 0) h->a[i] = last;
    return top;
}

HNode *huffman_build_from_freq(const int freq[256]) {
    HMinHeap h;
    hheap_init(&h);
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) hheap_push(&h, hnode_new((unsigned char)i, freq[i], NULL, NULL));
    }
    if (h.size == 0) return NULL;
    if (h.size == 1) {
        HNode *only = hheap_pop(&h);
        return hnode_new(0, only->freq, only, NULL);
    }
    while (h.size > 1) {
        HNode *a = hheap_pop(&h);
        HNode *b = hheap_pop(&h);
        HNode *parent = hnode_new(0, a->freq + b->freq, a, b);
        hheap_push(&h, parent);
    }
    return hheap_pop(&h);
}

void huffman_print_codes(HNode *root, char code[], int depth) {
    if (!root) return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        if (root->ch == ' ') printf("space: %s\n", code);
        else printf("%c: %s\n", root->ch, code);
        return;
    }
    code[depth] = '0';
    huffman_print_codes(root->left, code, depth + 1);
    code[depth] = '1';
    huffman_print_codes(root->right, code, depth + 1);
}

void huffman_destroy(HNode *root) {
    if (!root) return;
    huffman_destroy(root->left);
    huffman_destroy(root->right);
    free(root);
}

// ============================================================
// 5. 表达式树：由空格分隔后缀表达式构造并求值
// ============================================================

typedef struct ExprNode {
    char token[32];
    struct ExprNode *left;
    struct ExprNode *right;
} ExprNode;

static int is_op_token(const char *s) {
    return strlen(s) == 1 && strchr("+-*/", s[0]) != NULL;
}

static ExprNode *expr_new(const char *token) {
    ExprNode *p = (ExprNode *)calloc(1, sizeof(ExprNode));
    if (!p) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    snprintf(p->token, sizeof(p->token), "%s", token);
    return p;
}

ExprNode *expr_build_from_postfix(const char *postfix) {
    char buf[512];
    snprintf(buf, sizeof(buf), "%s", postfix);
    ExprNode *stack[128];
    int top = -1;
    char *tok = strtok(buf, " \t\n");
    while (tok) {
        ExprNode *node = expr_new(tok);
        if (is_op_token(tok)) {
            if (top < 1) {
                fprintf(stderr, "bad postfix expression\n");
                free(node);
                return NULL;
            }
            node->right = stack[top--];
            node->left = stack[top--];
        }
        stack[++top] = node;
        tok = strtok(NULL, " \t\n");
    }
    return top == 0 ? stack[top] : NULL;
}

double expr_eval(ExprNode *root) {
    if (!root) return 0.0;
    if (!is_op_token(root->token)) return strtod(root->token, NULL);
    double a = expr_eval(root->left);
    double b = expr_eval(root->right);
    switch (root->token[0]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0.0;
    }
}

void expr_inorder(ExprNode *root) {
    if (!root) return;
    if (is_op_token(root->token)) printf("(");
    expr_inorder(root->left);
    printf("%s", root->token);
    expr_inorder(root->right);
    if (is_op_token(root->token)) printf(")");
}

void expr_destroy(ExprNode *root) {
    if (!root) return;
    expr_destroy(root->left);
    expr_destroy(root->right);
    free(root);
}

// ============================================================
// 6. Trie 字典树：小写英文单词
// ============================================================

typedef struct TrieNode {
    int isword;
    struct TrieNode *child[26];
} TrieNode;

TrieNode *trie_new(void) {
    TrieNode *p = (TrieNode *)calloc(1, sizeof(TrieNode));
    if (!p) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return p;
}

void trie_insert(TrieNode *root, const char *word) {
    TrieNode *p = root;
    for (; *word; ++word) {
        if (!islower((unsigned char)*word)) continue;
        int idx = *word - 'a';
        if (!p->child[idx]) p->child[idx] = trie_new();
        p = p->child[idx];
    }
    p->isword = 1;
}

int trie_search(TrieNode *root, const char *word) {
    TrieNode *p = root;
    for (; *word; ++word) {
        if (!islower((unsigned char)*word)) return 0;
        int idx = *word - 'a';
        if (!p->child[idx]) return 0;
        p = p->child[idx];
    }
    return p->isword;
}

int trie_starts_with(TrieNode *root, const char *prefix) {
    TrieNode *p = root;
    for (; *prefix; ++prefix) {
        if (!islower((unsigned char)*prefix)) return 0;
        int idx = *prefix - 'a';
        if (!p->child[idx]) return 0;
        p = p->child[idx];
    }
    return 1;
}

void trie_destroy(TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < 26; ++i) trie_destroy(root->child[i]);
    free(root);
}

// ============================================================
// 7. 图：邻接表 + DFS/BFS
// ============================================================

#define MAXV 64

typedef struct EdgeNode {
    int to;
    int weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct Graph {
    int n;
    EdgeNode *adj[MAXV];
} Graph;

void graph_init(Graph *g, int n) {
    g->n = n;
    for (int i = 0; i < MAXV; ++i) g->adj[i] = NULL;
}

void graph_add_edge(Graph *g, int from, int to, int weight, int directed) {
    EdgeNode *e = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (!e) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    e->to = to;
    e->weight = weight;
    e->next = g->adj[from];
    g->adj[from] = e;
    if (!directed) graph_add_edge(g, to, from, weight, 1);
}

static void dfs_rec_impl(Graph *g, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);
    for (EdgeNode *e = g->adj[v]; e; e = e->next) {
        if (!visited[e->to]) dfs_rec_impl(g, e->to, visited);
    }
}

void graph_dfs(Graph *g, int start) {
    int visited[MAXV] = {0};
    dfs_rec_impl(g, start, visited);
}

void graph_bfs(Graph *g, int start) {
    int visited[MAXV] = {0};
    int q[MAXV], front = 0, rear = 0;
    visited[start] = 1;
    q[rear++] = start;
    while (front < rear) {
        int v = q[front++];
        printf("%d ", v);
        for (EdgeNode *e = g->adj[v]; e; e = e->next) {
            if (!visited[e->to]) {
                visited[e->to] = 1;
                q[rear++] = e->to;
            }
        }
    }
}

void graph_destroy(Graph *g) {
    for (int i = 0; i < g->n; ++i) {
        EdgeNode *p = g->adj[i];
        while (p) {
            EdgeNode *next = p->next;
            free(p);
            p = next;
        }
        g->adj[i] = NULL;
    }
}

// ============================================================
// Demo main：用于快速验证所有代码能跑通
// ============================================================

int main(void) {
    int vals[] = {50, 38, 30, 64, 58, 40, 10, 73, 70, 50, 60, 100, 35};
    int n = (int)(sizeof(vals) / sizeof(vals[0]));
    BTNodeptr root = NULL;
    for (int i = 0; i < n; ++i) root = bst_insert(root, vals[i]);

    printf("BST inorder(rec): "); inorder(root); printf("\n");
    printf("BST inorder(iter): "); inorder_iter(root); printf("\n");
    printf("BST preorder(iter): "); preorder_iter(root); printf("\n");
    printf("BST postorder(iter): "); postorder_iter(root); printf("\n");
    printf("BST levelorder: "); levelorder(root); printf("\n");
    printf("height=%d leaves=%d\n", bt_height(root), bt_leaf_count(root));
    printf("leaf value and height:\n"); print_leaves_with_height(root, 1);
    printf("ancestors of 70: "); print_bst_ancestors(root, 70); printf("\n");
    printf("search 64: %s\n", bst_search_iter(root, 64) ? "found" : "not found");
    root = bst_delete(root, 38);
    printf("after delete 38 inorder: "); inorder(root); printf("\n");

    int pre[] = {1, 2, 4, 5, 3, 6};
    int in[] = {4, 2, 5, 1, 3, 6};
    BTNodeptr rebuilt = build_from_pre_in(pre, 0, 5, in, 0, 5);
    printf("rebuilt postorder: "); postorder(rebuilt); printf("\n");
    destroy_tree(&rebuilt);

    AVLNode *avl = NULL;
    int av[] = {4, 5, 6, 7, 8};
    for (int i = 0; i < 5; ++i) avl = avl_insert(avl, av[i]);
    printf("AVL inorder: "); avl_inorder(avl); printf("\n");

    MaxHeap heap;
    heap_build(&heap, vals, n);
    int top1 = heap_pop(&heap);
    int top2 = heap_pop(&heap);
    int top3 = heap_pop(&heap);
    printf("heap pop top3: %d %d %d\n", top1, top2, top3);

    const char *text = "time tries truth";
    int freq[256] = {0};
    for (const unsigned char *p = (const unsigned char *)text; *p; ++p) freq[*p]++;
    HNode *hroot = huffman_build_from_freq(freq);
    char code[256];
    printf("Huffman codes for '%s':\n", text);
    huffman_print_codes(hroot, code, 0);

    ExprNode *expr = expr_build_from_postfix("2 3 + 4 5 - *");
    printf("expr infix: "); expr_inorder(expr); printf(" = %.2f\n", expr_eval(expr));

    TrieNode *trie = trie_new();
    trie_insert(trie, "apple");
    trie_insert(trie, "app");
    trie_insert(trie, "cat");
    printf("trie search apple=%d, starts app=%d, search ap=%d\n",
           trie_search(trie, "apple"), trie_starts_with(trie, "app"), trie_search(trie, "ap"));

    Graph g;
    graph_init(&g, 5);
    graph_add_edge(&g, 0, 1, 1, 0);
    graph_add_edge(&g, 0, 2, 1, 0);
    graph_add_edge(&g, 1, 3, 1, 0);
    graph_add_edge(&g, 2, 4, 1, 0);
    printf("DFS from 0: "); graph_dfs(&g, 0); printf("\n");
    printf("BFS from 0: "); graph_bfs(&g, 0); printf("\n");

    graph_destroy(&g);
    trie_destroy(trie);
    expr_destroy(expr);
    huffman_destroy(hroot);
    avl_destroy(avl);
    destroy_tree(&root);
    return 0;
}

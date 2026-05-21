#include <stdio.h>
#include <stdlib.h>

typedef struct TNode
{
    int index;
    struct TNode *lchild;
    struct TNode *mchild;
    struct TNode *rchild;
    int Num; // 表示客流量
} TNode;

struct temp
{
    int index; 
    int Num;
};

TNode *tnode_new(int data); // 创建一个树节点, 可选择是否传入客流量，若不传入客流量则为枝节点
TNode *create_tree(); // 创建机场的树
TNode *search_tnode(TNode *root, int data); // 寻找指定编号的节点
int tree_leaf_count(TNode *root); // 遍历返回叶子节点的数量
void insert_num(TNode *root); // 为登记口注册客流量
void collect_value(TNode *root, struct temp *arr, int *count); // 遍历树 收集所有数值
void fill_value(TNode *root, struct temp *arr, int *count); // 遍历树 按照同样的方式填回去
int cmp(const void *p, const void *q); // qsort比较函数
void order_tree(TNode *root); // 为树进行排序

int main(void)
{
    // test1 
    TNode *root = create_tree();

    // test2
    insert_num(root);

    // test3
    order_tree(root);

    // TNode *root = create_tree();
    // order_tree(root);

    return 0;
}

TNode *tnode_new(int data)
{
    TNode *p = (TNode *)malloc(sizeof(TNode));
    if (p == NULL)
        return NULL;

    p -> index = data;
    p -> Num = 0;
    p -> lchild = NULL;
    p -> rchild = NULL;
    p -> mchild = NULL;

    return p;
}

TNode *create_tree()
{
    TNode *root = NULL;
    int num;
    int data, ldata, mdata, rdata;
    
    scanf("%d", &num);
    while (num != -1)
    {
        data = ldata = mdata = rdata = -1;
        data = num;
        // 进行数值读取并根据顺序存入不同的位置方便后续分流
        for (int i = 1; i < 10000; i++)
        {
            scanf("%d", &num);

            if (num == -1)
                break;

            if (i == 1)
                ldata = num;
            else if (i == 2 && num >= 100)
                mdata = num;
            else if (i == 2 && num < 100)
                rdata = num;
            else if (i == 3)
                rdata = num;
        }

        // 创建一个临时节点
        TNode *fakeroot = tnode_new(data);
        if (ldata != -1)
            fakeroot -> lchild = tnode_new(ldata);
        if (mdata != -1)
            fakeroot -> mchild = tnode_new(mdata);
        if (rdata != -1)
            fakeroot -> rchild = tnode_new(rdata);

        if (root == NULL)
            root = fakeroot;
        else
        {
            // 找值对应的节点
            TNode *real = search_tnode(root, data);
            real -> lchild = fakeroot -> lchild;
            real -> mchild = fakeroot -> mchild;
            real -> rchild = fakeroot -> rchild;
            free(fakeroot);
        }
        
        scanf("%d", &num);
        // 树建立完成
        if (num == -1)
            break;
    }

    return root;
}

TNode *search_tnode(TNode *root, int data)
{
    if (root == NULL)
        return NULL;

    if (root -> index == data)
        return root;
    
    if (search_tnode(root -> lchild, data))
        return search_tnode(root -> lchild, data);
    else if (search_tnode(root -> mchild, data))
        return search_tnode(root -> mchild, data);
    else if (search_tnode(root -> rchild, data))
        return search_tnode(root -> rchild, data);

    return NULL;
}

int tree_leaf_count(TNode *root)
{
    if (root == NULL)
        return 0;
    if (root -> lchild == NULL && root -> mchild == NULL 
        && root -> rchild == NULL)
        return 1;
    
    return tree_leaf_count(root -> lchild) + 
    tree_leaf_count(root -> mchild) + tree_leaf_count(root -> rchild);
}

void insert_num(TNode *root)
{
    int index; int client;
    int num = tree_leaf_count(root);

    for (int i = 0; i < num; i++)
    {
        scanf("%d%d", &index, &client);
        TNode *p = search_tnode(root, index);
        p -> Num = client;
    }
}

void collect_value(TNode *root, struct temp *arr, int *count)
{
    if (root == NULL)
        return ;

    if (root -> lchild == NULL && root -> mchild == NULL && 
        root -> rchild == NULL)
    {    
        arr[(*count)].index = root -> index;
        arr[(*count)++].Num = root -> Num;
    }

    collect_value(root -> lchild, arr, count);
    collect_value(root -> mchild, arr, count);
    collect_value(root -> rchild, arr, count);
}

void fill_value(TNode *root, struct temp *arr, int *count)
{
    if (root == NULL)
        return ;

    if (root -> lchild == NULL && root -> mchild == NULL && 
        root -> rchild == NULL)
    {
        printf("%d->%d\n", root -> index, arr[(*count)++].index);
        root -> index = arr[(*count)].index;
        root -> Num = arr[(*count)].Num;
    }

    fill_value(root -> lchild, arr, count);
    fill_value(root -> mchild, arr, count);
    fill_value(root -> rchild, arr, count);
}

int cmp(const void *p, const void *q)
{
    struct temp *a = (struct temp *)p;
    struct temp *b = (struct temp *)q;

    if (a -> Num > b -> Num)
        return -1;
    else if (a -> Num < b -> Num)
        return 1;
    else if (a -> index < b -> index)
        return -1;
    else if (a -> index > b -> index)
        return 1;
    else
        return 0;
}

void order_tree(TNode *root)
{
    int num = 0;
    int size = tree_leaf_count(root);
    struct temp obj[size];

    collect_value(root, obj, &num);

    qsort(obj, size, sizeof(struct temp), cmp);

    num = 0;
    fill_value(root, obj, &num);
}
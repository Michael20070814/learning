#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *lchild, *rchild;
} BTNode;

// 二叉查找树节点的插入
BTNode *bst_insert(BTNode *root, int data);
void print_leaves_with_height(BTNode *root, int height); // 打印对应叶节点的值和对应的高度
BTNode *bt_new(int data); // 添加新的节点

int main(void)
{
    int num; int data;
    BTNode *root = NULL;

    // test1 
    // root = bst_insert(root, 2);
    // root = bst_insert(root, 6);
    // root = bst_insert(root, 1);

    // test2
    // root = bst_insert(root, 2);
    // root = bst_insert(root, 6);
    // root = bst_insert(root, 1);
    // print_leaves_with_height(root, 1);

    scanf("%d", &num);

    for (int i = 0; i < num; i++)
    {
        scanf("%d", &data);
        root = bst_insert(root, data);
    }

    print_leaves_with_height(root, 1);

    return 0;
}

BTNode *bst_insert(BTNode *root, int data)
{
    if (root == NULL)
        return bt_new(data);

    if (root -> data <= data)
        root -> rchild = bst_insert(root -> rchild, data);
    else
        root -> lchild = bst_insert(root -> lchild, data);

    return root;
}

BTNode *bt_new(int data)
{
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));

    if (p == NULL)
        return NULL;
    
    p -> data = data;
    p -> lchild = NULL;
    p -> rchild = NULL;
    return p;
}

void print_leaves_with_height(BTNode *root, int height)
{
    if (root == NULL)
        return ;

    print_leaves_with_height(root -> lchild, height + 1);
    
    if (root -> lchild == NULL && root -> rchild == NULL)
        printf("%d %d\n", root -> data, height);

    print_leaves_with_height(root -> rchild, height + 1);
}
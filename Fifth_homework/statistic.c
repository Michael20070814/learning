#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define LENGTH 1000
#define SIZE 50

typedef struct TNode
{
    char vocab[SIZE];
    struct TNode *lchild;
    struct TNode *rchild;
    int times;
} TNode;

TNode *bst_new(char *vocab); // 创建二叉查找树的节点
TNode *bst_insert(TNode *root, char *vocab); // 在二叉查找树上插入节点p
// TNode *search_tnode(char *vocab); // 根据单词查找所需根，未找到则返回NULL
void extract_alpha(char *vocab); // 提取字母
TNode *create_tree(); // 完成树的创建
void init_print(TNode *root); // 打印根的值，打印根的右节点的值，打印根的右节点的右节点的值
void print(TNode *root); // 中序遍历按照字典序输出单词词频

int main(void)
{
    // test 0
    // char p[] = "1975";
    // extract_alpha(p);

    // test 1
    // TNode *root = create_tree();

    // test2
    // init_print(root);

    // test3
    // print(root);

    TNode *root = create_tree();

    init_print(root);

    print(root);

    return 0;
}

TNode *bst_new(char *vocab)
{
    TNode *p = (TNode *)malloc(sizeof(TNode));

    if (p == NULL)
        return NULL;

    snprintf(p -> vocab, sizeof(p -> vocab), "%s", vocab);
    p -> times = 1;
    p -> lchild = NULL;
    p -> rchild = NULL;

    return p;
}

TNode *bst_insert(TNode *root, char *vocab)
{
    if (root == NULL)
        return bst_new(vocab);

    if (strcmp(root -> vocab, vocab) < 0)
        root -> rchild = bst_insert(root -> rchild, vocab);
    else if (strcmp(root -> vocab, vocab) > 0)
        root -> lchild = bst_insert(root -> lchild, vocab);
    else
        root -> times++;
    
    return root;
}

// TNode *search_tnode(char *vocab)
// {

// }

TNode *create_tree()
{
    TNode *root = NULL;
    FILE *fp = fopen("article.txt", "r");

    char buffer[LENGTH];

    while (fgets(buffer, LENGTH - 1, fp) != NULL)
    {
        char *tok = strtok(buffer, " ,.()-”;\t\n");
        while (tok)
        {
            extract_alpha(tok);

            if (tok[0] == '\0')
            {
                tok = strtok(NULL, " ,.()-”;\t\n");
                continue;
            }

            // 全部转换为小写
            for (int i = 0; tok[i] != '\0'; i++)
                tok[i] = tolower(tok[i]);

            root = bst_insert(root, tok); // 按单词进行插入 不过这里需要debug一下这个tok的形式是否正确
            tok = strtok(NULL, " ,.()-”;\t\n");
        }
        
    }

    fclose(fp);

    return root;
}

void init_print(TNode *root)
{
    TNode *p = root;

    for (int num = 0; num < 3 && p != NULL; num++)
    {
        printf("%s ", p -> vocab);
        p = p -> rchild;
    }

    printf("\n");
}

void print(TNode *root)
{
    if (root == NULL)
        return ;

    print(root -> lchild);
    printf("%s %d\n", root -> vocab, root -> times);
    print(root -> rchild);
}

void extract_alpha(char *vocab)
{
    char buffer[SIZE];

    char *p = buffer;
    char *q = vocab;

    while (*q != '\0')
    {
        if (isalpha(*q))
        {    
            *p = *q;
            p++;
        }
        q++;
    }

    *p = '\0';
    strcpy(vocab, buffer);
}
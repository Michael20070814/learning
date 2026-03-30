#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 2000
#define LENGTH 20

typedef struct wordtimes
{
    char word[20];
    int times;
    struct wordtimes *next;
} wordtimes;

void InsertNode(wordtimes *result, wordtimes *node);
char* retrieve_word(char buffer[], int *num);
wordtimes* input(char *filename);

int main(void)
{
    char filename[] = "article.txt";

    wordtimes *head = input(filename), *p = NULL;
    p = head;

    while (p -> next != NULL)
    {
        printf("%s %d\n", p -> next -> word, p -> next -> times);
        p = p -> next;
    }

    wordtimes *cur = head;
    while (cur != NULL)
    {
        wordtimes *next = cur->next;
        free(cur);
        cur = next;
    }

    return 0;
}

void InsertNode(wordtimes *sentinel, wordtimes *node)
{
    wordtimes *cur = sentinel;  // 从哨兵节点开始遍历，不再需要二级指针

    while (cur->next != NULL)
    {
        if (strcmp(cur->next->word, node->word) == 0)
        {
            // 找到相同单词，次数+1，释放新节点
            cur->next->times += 1;
            free(node);
            return;
        }

        // 找到第一个字典序大于node的位置，插在其前面
        if (strcmp(cur->next->word, node->word) > 0)
        {
            node->next = cur->next;
            cur->next = node;
            return;
        }

        cur = cur->next;
    }

    // 已到链表末尾，直接追加
    node->next = NULL;
    cur->next = node;
}

wordtimes* input(char *filename)
{
    FILE *fp = fopen(filename, "r");
    char buffer[MAX] = {0};

    size_t n = fread(buffer, 1, MAX - 1, fp);
    buffer[n] = '\0';
    fclose(fp);

    wordtimes *head, *p = NULL;
    head = (wordtimes *) malloc(sizeof(wordtimes));
    head -> next = NULL;
    head -> word[0] = '\0';
    head -> times = 0;

    char *token;
    int skip = 0;
    char *q = buffer;
    while ((token = retrieve_word(q, &skip)) != NULL)
    {
        p = (wordtimes *) malloc(sizeof(wordtimes));
        strcpy(p -> word, token);
        p -> times = 1;
        p -> next = NULL;
        
        InsertNode(head, p);
        free(token);
        q = q + skip;
    }

    return head;
}

char* retrieve_word(char buffer[], int *num)
{
    int i = 0;
    int start = -1;
    int end = -1;

    // 跳过前导非字母字符，找到第一个字母
    while (buffer[i] != '\0')
    {
        if (isalpha((unsigned char)buffer[i]))
        {
            start = i;
            break;
        }
        i++;
    }

    // 没有找到任何字母，返回NULL
    if (start == -1)
    {
        *num = i;
        return NULL;
    }

    // 从start开始，读到第一个非字母字符为止
    while (buffer[i] != '\0' && isalpha((unsigned char)buffer[i]))
    {
        i++;
    }
    end = i; // end是单词后第一个非字母字符的位置

    // 分配并构造结果字符串
    int len = end - start;
    char *word = (char *)malloc((len + 1) * sizeof(char));
    if (word == NULL) return NULL;

    for (int j = 0; j < len; j++)
    {
        word[j] = tolower((unsigned char)buffer[start + j]);
    }
    word[len] = '\0';

    // num返回本次向后读取的字符总数（含前导非字母部分和单词本身）
    *num = end;
    return word;
}
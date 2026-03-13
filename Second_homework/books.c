#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOK_SIZE 501
#define BOOK_NAME 51
#define AUTHOR_NAME 21
#define ROW_LENGTH 1024
#define PUBLISH_AUTHORITY 31
#define PUBLISH_DATE 11

typedef struct book
{
    char book_name[BOOK_NAME];
    char book_author[AUTHOR_NAME];
    char book_press[PUBLISH_AUTHORITY];
    char book_date[PUBLISH_DATE];
    struct book *next_book;
} book;

book *input(char *filename); // 单步存入
void insert_book(char *buffer, book **head);
void search_book(char *buffer, book *head);
void delete_book(char *buffer, book **head);
void output(book *head, char *filename);

int main(void)
{
    char file_in[] = "books.txt";
    char file_out[] = "ordered.txt";

    book *head = input(file_in);

    int num;
    scanf("%d", &num);
    getchar();
    while (num != 0)
    {
        if (num == 1)
        {
            char *buffer = (char *) malloc (sizeof(char) * ROW_LENGTH);
            fgets(buffer, ROW_LENGTH, stdin);
            insert_book(buffer, &head);
            free(buffer);
        }
        else if (num == 2)
        {
            char *buffer = (char *) malloc (sizeof(char) * ROW_LENGTH);
            fgets(buffer, ROW_LENGTH, stdin);
            search_book(buffer, head);
            free(buffer);
        }
        else if (num == 3)
        {
            char *buffer = (char *) malloc (sizeof(char) * ROW_LENGTH);
            fgets(buffer, ROW_LENGTH, stdin);
            delete_book(buffer, &head);
            free(buffer);
        }
        scanf("%d", &num);
        getchar();
    }
    output(head, file_out);

    free(head);

    return 0;
}

book *input(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return NULL;

    book *head = NULL;  
    char line[ROW_LENGTH];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        /* 去掉行尾的换行符 */
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0')
            continue;   /* 跳过空行 */

        /* 分配新节点 */
        book *node = (book *)calloc(1, sizeof(book));
        if (node == NULL)
        {
            fclose(fp);
            return head;
        }

        /* 从当前行解析四个字段（空白符分隔） */
        if (sscanf(line, "%s %s %s %s",
                   node->book_name,
                   node->book_author,
                   node->book_press,
                   node->book_date) != 4)
        {
            free(node);     /* 格式不符则丢弃该行 */
            continue;
        }
        node->next_book = NULL;

        /* 情况一：链表为空，或新节点应插在头部 */
        if (head == NULL || strncmp(node->book_name, head->book_name, BOOK_NAME) < 0)
        {
            node->next_book = head;
            head = node;
        }
        else
        {
            /* 情况二：遍历链表，找到第一个比新节点大的节点的前驱 */
            book *cur = head;
            while (cur->next_book != NULL &&
                   strncmp(cur->next_book->book_name, node->book_name, BOOK_NAME) <= 0)
            {
                cur = cur->next_book;
            }
            /* 将新节点插入 cur 之后 */
            node->next_book = cur->next_book;
            cur->next_book = node;
        }
    }

    fclose(fp);
    return head;
}

void insert_book(char *buffer, book **head)
{
    if (buffer == NULL || head == NULL)
        return;

    /* 分配新节点并解析 buffer */
    book *node = (book *)calloc(1, sizeof(book));
    if (node == NULL)
        return;

    if (sscanf(buffer, "%s %s %s %s",
               node->book_name,
               node->book_author,
               node->book_press,
               node->book_date) != 4)
    {
        free(node);
        return;
    }
    node->next_book = NULL;

    /* 情况一：链表为空，或新节点应插在头部 */
    if (*head == NULL || strncmp(node->book_name, (*head)->book_name, BOOK_NAME) < 0)
    {
        node->next_book = *head;
        *head = node;         /* 直接修改调用方的 head 指针 */
    }
    else
    {
        /* 情况二：遍历链表，找到合适的插入位置 */
        book *cur = *head;
        while (cur->next_book != NULL &&
               strncmp(cur->next_book->book_name, node->book_name, BOOK_NAME) <= 0)
        {
            cur = cur->next_book;
        }
        node->next_book = cur->next_book;
        cur->next_book = node;
    }
}

void search_book(char *buffer, book *head)
{
    if (buffer == NULL || head == NULL)
        return;

    /* 去掉 buffer 末尾可能存在的换行符 */
    buffer[strcspn(buffer, "\n")] = '\0';

    book *cur = head;
    while (cur != NULL)
    {
        if (strstr(cur->book_name, buffer) != NULL)
        {
            printf("%-50s%-20s%-30s%-10s\n",
                   cur->book_name,
                   cur->book_author,
                   cur->book_press,
                   cur->book_date);
        }
        cur = cur->next_book;
    }
}

void delete_book(char *buffer, book **head)
{
    if (buffer == NULL || head == NULL || *head == NULL)
        return;

    /* 去掉 buffer 末尾可能存在的换行符 */
    buffer[strcspn(buffer, "\n")] = '\0';

    book *prev = NULL;
    book *cur  = *head;

    while (cur != NULL)
    {
        if (strstr(cur->book_name, buffer) != NULL)
        {
            book *to_free = cur;

            if (prev == NULL)
            {
                /* 删除的是头节点，更新 head */
                *head = cur->next_book;
            }
            else
            {
                /* 删除的是中间或尾节点，跳过当前节点 */
                prev->next_book = cur->next_book;
            }

            cur = cur->next_book;   /* 先移动指针，再释放 */
            free(to_free);
        }
        else
        {
            prev = cur;
            cur  = cur->next_book;
        }
    }
}

void output(book *head, char *filename)
{
    if (head == NULL || filename == NULL)
        return;

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
        return;

    book *cur = head;
    while (cur != NULL)
    {
        fprintf(fp, "%-50s%-20s%-20s%-10s\n",
                cur->book_name,
                cur->book_author,
                cur->book_press,
                cur->book_date);
        cur = cur->next_book;
    }

    fclose(fp);
}
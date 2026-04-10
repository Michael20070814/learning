#include <stdio.h>
#include <stdlib.h>
#define LEN 5

typedef struct Node
{
    int num;
    struct Node *next;
    int times;
} Node;

int InsertNode(Node *head, int input);
void print(Node *head);

int main(void)
{
    Node *head = (Node *) malloc(sizeof(Node));
    head -> num = 0;
    head -> next = NULL;
    head -> times = 0;

    int times; int InsertTimes = 0;
    int num;

    scanf("%d", &times);

    for (int i = 0; i < times; i++)
    {    
        scanf("%d", &num);
        InsertTimes += InsertNode(head, num);
    }

    printf("%d\n", InsertTimes);
    print(head);
}

int InsertNode(Node *head, int input)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p -> next = NULL;
    p -> times = 1;
    p -> num = input;
    if (head -> next == NULL)
    {
        head -> next = p;
        return 0;
    }

    int result = 0; int flag = 0;
    Node *iter = head;

    while (iter -> next != NULL)
    {
        result++;
        if (iter -> next -> num == input)
        {
            flag = 1;
            break;
        }
        iter = iter -> next;
    }

    if (flag == 0)
        iter -> next = p;
    else
    {
        if (iter == head)
        {    
            head -> next -> times += 1;
            return result;
        }
        Node *temp = iter -> next -> next;
        iter -> next -> next = head -> next;
        head -> next = iter -> next;
        iter -> next = temp;
        head -> next -> times += 1;
        free(p);
    }
    
    return result;
}

void print(Node *head)
{
    Node *p = head -> next;
    for (int i = 0; i < LEN; i++)
    {
        if (p == NULL)
            break;
        
        printf("%d %d\n", p -> num, p -> times);

        p = p -> next;
    }
}

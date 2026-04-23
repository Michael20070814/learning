#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int num;
    struct Node *next;
} Node;

Node* CreateLinkList(int num);
Node* FindSmallestNode(Node *head);
Node* PrintAndDeleteNode(Node *head, Node *flag);

int main(void)
{
    int num;

    scanf("%d", &num);

    Node *head = CreateLinkList(num);
    Node *q = head;
    Node *p = NULL;

    while ((p = FindSmallestNode(q)) != NULL)
        q = PrintAndDeleteNode(q, p);

    return 0;
}

Node* CreateLinkList(int num)
{
    Node *head = NULL;
    Node *tail = NULL;
    
    for (int i = 0; i < num; i++)
    {
        int temp;
        Node *q = (Node *)malloc(sizeof(Node));
        scanf("%d", &temp);
        q -> num = temp;
        q -> next = NULL;
        if (head == NULL)
            head = q;
        else
            tail -> next = q;
        
        tail = q;
    }
    tail -> next = head;

    return head;
}

Node* FindSmallestNode(Node *head)
{
    if (head == NULL)
        return NULL;

    int small = head -> num;
    Node *result = head;

    Node *q = head;
    q = q -> next;
    while (q != head)
    {
        if (small > q -> num)
        {    
            small = q -> num;
            result = q;
        }
        q = q -> next;
    }

    return result;
}

Node* PrintAndDeleteNode(Node *head, Node *flag)
{
    if (head == head -> next)
    {    
        printf("%d", head -> num);
        free(head);
        return NULL;
    }

    Node *before = head;
    while (before -> next != head)
        before = before -> next;

    Node *iter = head;
    while (iter != flag)
    {
        printf("%d ", iter -> num);
        iter = iter -> next;
        before = before -> next;
    }

    printf("%d\n", iter -> num);

    before -> next = iter ->next;
    free(iter);
    iter = before -> next;

    return iter;
}
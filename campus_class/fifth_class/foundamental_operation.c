#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
int main(void)
{
    int temp, i;
    struct Node *head, *p;
    scanf("%d", &temp);
    head = malloc(sizeof(struct Node));
    head -> data = temp;
    head -> next = NULL;
    scanf("%d", &temp);
    while (temp > 0)
    {
        p = head;
        head = malloc(sizeof(struct Node));
        head -> data = temp;
        head -> next = p;
        scanf("%d", &temp);
        i++; 
    }
    p = head;
    while (p != NULL)
    {
        printf("%d ", p -> data);
        p = p -> next;
    }

    free(head);
    free(p);
    return 0;
}
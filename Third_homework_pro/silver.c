#include <stdio.h>
#include <stdlib.h>
typedef struct silver
{
    int weight;
    struct silver *next;
} silver;

void buy_silver(silver *head, int input);
void sell_silver(silver *head, int input);
void merge_silver(silver *head);
void print_silver(silver *head);

int main(void)
{
    int num;
    silver *head = (silver *)malloc(sizeof(silver));
    head -> next = NULL;
    head -> weight = 0;

    while (scanf("%d", &num) == 1 && num != 999999)
    {
        if (num > 0)
            buy_silver(head, num);
        else if (num < 0)
            sell_silver(head, num);
        else
            merge_silver(head);
    }

    print_silver(head);
    free(head);

    return 0;
}

void buy_silver(silver *head, int input)
{
    if (head -> next == NULL)
    {
        silver *p = (silver *) malloc(sizeof(silver));
        p -> next = NULL;
        p -> weight = input;
        head -> next = p;
    }
    else
    {
        silver *p = (silver *) malloc(sizeof(silver));
        p -> next = NULL;
        p -> weight = input;
        silver *q = head;

        while (q -> next != NULL && q -> next -> weight < input)
            q = q -> next;
        p -> next = q -> next;
        q -> next = p;
    }
}

void sell_silver(silver *head, int input)
{
    silver *q = head -> next;
    int sum = 0;
    input = abs(input);

    while (q != NULL)
    {
        sum += q -> weight;
        q = q -> next;
    }

    if (input > sum)
        return ;
    
    int size = 0;
    q = head -> next;

    while (q != NULL)
    {
        if (size >= input)
            break;
        
        if (input - size >= q -> weight)
        {
            size += q -> weight;
            head -> next = q -> next;
            free(q);
            q = head -> next;
        }
        else 
        {    
            q -> weight -= input - size;
            size += input - size;
        }
    }
}

void merge_silver(silver *head)
{
    silver *q = head -> next;
    int sum = 0;

    while (q != NULL)
    {
        if (q -> weight >= 10)
            break;
        
        sum += q -> weight;
        head -> next = q -> next;
        free(q);
        q = head -> next;
    }

    if (sum == 0)
        return ;

    silver *p = (silver *) malloc(sizeof(silver));
    p -> next = NULL;
    p -> weight = sum;
    q = head;
    while (q -> next != NULL && q -> next -> weight < sum)
        q = q -> next;

    p -> next = q -> next;
    q -> next = p;
}

void print_silver(silver *head)
{
    silver *p = head -> next;
    silver *temp;

    while (p != NULL)
    {
        printf("%d ", p -> weight);
        temp = p -> next;
        free(p);
        p = temp;
    }
}
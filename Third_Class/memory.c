#include <stdio.h>
#include <stdlib.h>
typedef struct memory
{
    int location;
    int size;
    struct memory *next;
} memory;

memory* input(int num, memory **tail);
void use_the_memory(memory **before, memory **cur, int size);
void print(memory *cur);

int main(void)
{
    int num;

    scanf("%d", &num);
    memory *tail = NULL;
    memory *head = input(num, &tail);

    int block;
    memory *cur = head;

    while ((scanf("%d", &block)) == 1 && block != -1)
        use_the_memory(&tail, &cur, block);

    print(cur);
}

memory* input(int num, memory **tail)
{
    memory *head = NULL;
    memory *cur = NULL;

    for (int i = 0; i < num; i++) {
        memory *node = (memory*)malloc(sizeof(memory));
        scanf("%d %d", &node->location, &node->size);
        node->next = NULL;

        if (head == NULL) {
            head = node;
            cur = node;
        } else {
            cur->next = node;
            cur = node;
        }
    }

    // 尾结点指向头结点，形成循环链表
    cur->next = head;
    *tail = cur;

    return head;
}

void use_the_memory(memory **before, memory **cur, int size)
{
    memory *last = *before;
    memory *current = *cur;
    int subtract; int min = -1;
    memory *flag = *cur;

    // find the minimum
    while (current -> next != *cur)
    {
        subtract = current -> size - size;
        if ((min == -1 && subtract >= 0) || (subtract >= 0 && subtract < min))
        {
            min = subtract;
            flag = current;
        }
        current = current -> next;
    }
    // move the last time
    subtract = current -> size - size;
    if ((min == -1 && subtract >= 0) || (subtract >= 0 && subtract < min))
    {
        min = subtract;
        flag = current;
    }
    current = current -> next;
    while (current != flag)
    {
        current = current -> next;
        last = last -> next;
    }
    if (min == 0 && current == current -> next)
    {    
        *cur = NULL;
        *before = NULL;
        return ;
    }
    else if (min == 0)
    {    
        last -> next = current -> next;
        free(current);
        current = last -> next;
    }
    else if (min != -1)
        current -> size -= size;

    *before = last;
    *cur = current;
}

void print(memory *cur)
{
    memory *current = cur;

    if (cur == NULL)
        return ;

    while (current -> next != cur)
    {
        printf("%d %d\n", current -> location, current -> size);
        current = current -> next;
    }

    printf("%d %d\n", current -> location, current -> size);
}
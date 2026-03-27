#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

typedef struct unknown
{
    int coefficient;
    int exponent;
    struct unknown *next;
} unknown;

unknown* input(void);
void InsertNode(unknown **result, unknown *node);
unknown* multi(unknown *input1, unknown *input2);
void print(unknown *input);

int main(void)
{
    unknown *polynomial1;
    unknown *polynomial2;

    polynomial1 = input();
    polynomial2 = input();

    unknown *result;

    result = multi(polynomial1, polynomial2);

    print(result);

    return 0;
}

unknown* input(void)
{
    unknown *list = NULL, *p, *tail;
    char buffer[LEN];
    
    fgets(buffer, sizeof(buffer), stdin);

    int coeff, expon, n; char *ptr = buffer;
    while (sscanf(ptr, "%d%d%n", &coeff, &expon, &n) == 2)
    {
        p = (unknown *) malloc(sizeof(unknown));
        if (p == NULL)
            return NULL;

        p -> coefficient = coeff;
        p -> exponent = expon;
        p -> next = NULL;

        if (list == NULL)
        {    
            list = p;
            tail = p;
        }
        else
        {
            tail -> next = p;
            tail = tail -> next;
        }
        ptr += n;
    }

    return list;
}

unknown* multi(unknown *input1, unknown *input2)
{
    unknown *result = NULL, *p;
    unknown *iterate1, *iterate2;
    iterate1 = input1;

    while (iterate1 != NULL)
    {
        iterate2 = input2;
        while (iterate2 != NULL)
        {
            p = (unknown *) malloc (sizeof(unknown *));
            p -> coefficient = iterate1 -> coefficient * iterate2 -> coefficient;
            p -> exponent = iterate1 -> exponent + iterate2 -> exponent;
            p -> next = NULL;
            InsertNode(&result, p);
            iterate2 = iterate2 -> next;
        }
        iterate1 = iterate1 -> next;
    }

    return result;
}

void InsertNode(unknown **result, unknown *node)
{
    if (*result == NULL)
    {    
        *result = node;
        return;
    }
    
    unknown *cur = *result;

    while (cur != NULL) 
    {
        if (cur->exponent == node->exponent)
        {
            // equal exponent
            cur->coefficient += node->coefficient;
            return;
        }

        // 找到第一个exponent小于node的位置，插在其前面
        if (cur->next == NULL || cur->next->exponent < node->exponent)
        {
            node->next = cur->next;
            cur->next = node;
            return;
        }

        cur = cur->next;
    }
}

void print(unknown *input)
{
    unknown *cur = input;

    while (cur != NULL)
    {
        printf("%d %d ", cur -> coefficient, cur -> exponent);
        cur = cur -> next;
    }
}
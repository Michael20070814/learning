#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define LEN 500

typedef struct unknown
{
    int coefficient;
    int exponent;
    struct unknown *next;
} unknown;

int main(void)
{
    unknown list;
    unknown *p;

    list.exponent = 0;
    list.coefficient = 0;
    list.next = NULL;

    int count = 0;

    int coeff, expon; 
    while (scanf("%d%d", &coeff, &expon) == 2)
    {
        if (coeff == 0 && expon == -1)
            break;
        p = (unknown *) malloc(sizeof(unknown));

        p -> coefficient = coeff;
        p -> exponent = expon;
        p -> next = NULL;

        if (list.next == NULL)
        {    
            list.next = p;
        }
        else
        {
            unknown *iter;
            unknown *before;
            before = &list;
            iter = list.next;
            int flag = 0;
            while (iter != NULL && iter -> exponent >= p ->exponent)
            {
                count++;
                if (iter -> exponent == p -> exponent)
                {    
                    flag = 1;
                    break;
                }
                before = before -> next;
                iter = iter -> next;
            }

            if (flag == 1)
            {    
                if (iter -> exponent == p ->exponent)
                    before -> next = iter -> next;
                else
                    iter ->coefficient += p ->coefficient;
            }
            else if (iter == NULL)
                before -> next = p;
            else
            {    
                before -> next = p;
                p -> next = iter;
            }
        }
    
    }

    unknown *iter = &list;

    while (iter -> next != NULL)
    {
        printf("%d %d\n", iter -> next -> coefficient, iter ->next -> exponent);
        iter = iter ->next;
    }
    printf("%d\n", count);

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
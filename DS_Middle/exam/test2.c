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

unknown list;
int count;

void init(); // 初始化链表
void InsertNode(int coeff, int expon); // 插入节点
void print(); // 打印最后的多项式

int main(void)
{
    init();

    // 测试用例
    // InsertNode(100, 25);
    // InsertNode(8, 1000);
    // InsertNode(-64, 25);
    // InsertNode(100, 0);
    // InsertNode(-36, 25);
    // InsertNode(-6, 1000);
    // InsertNode(-50, 1);
    
    // print();

    int coeff, expon; 
    while (scanf("%d%d", &coeff, &expon) == 2)
    {
        if (coeff == 0 && expon == -1)
            break;

        InsertNode(coeff, expon);
    }

    print();

    return 0;
}

void init()
{
    list.exponent = 0;
    list.coefficient = 0;
    list.next = NULL;
    count = 0;
}

void InsertNode(int coeff, int expon)
{
    unknown *p = (unknown *) malloc(sizeof(unknown));

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

        // 比较大小确定插入位置
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

        // 补足完全没进入循环的情况
        if (iter != NULL && iter -> exponent < p -> exponent)
            count++;

        // 指数相等，则只需要进行系数变换
        if (flag == 1)
        {    
            // 恰好是相反数
            if (iter -> coefficient == -p -> coefficient)
            {    
                before -> next = iter -> next;
                free(iter);
            }
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

void print()
{
    unknown *iter = &list;

    while (iter -> next != NULL)
    {
        printf("%d %d\n", iter -> next -> coefficient, iter ->next -> exponent);
        iter = iter ->next;
    }
    printf("%d\n", count);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

typedef struct dish
{
    char code[SIZE];
    int num;
    int price;
} dish;

dish sale[100]; // 存储菜的品目 全局存储默认为0
int count = 0; // 用来记录已有的菜

int find_dish(char *name); // 找出对应菜品的名字所在的位置，若不存在，则返回-1
void input(); // 从标准输入中获取菜品 并且录入系统
int cmp(const void *a, const void *b); // qsort标准比较函数
void print(); // 按销售额输出菜品和总销售额

int main(void)
{
    input();

    qsort(sale, count, sizeof(dish), cmp);

    print();

    return 0;
}

int find_dish(char *name)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(name, sale[i].code) == 0)
            return i;
    }

    return -1;
}

void input()
{
    int num;

    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        int rubbish;
        char buffer[SIZE];
        int num;
        int price;

        scanf("%d%s%d%d", &rubbish, buffer, &num, &price);

        int flag = find_dish(buffer);

        if (flag == -1)
        {
            strcpy(sale[count].code, buffer);
            sale[count].num = num;
            sale[count].price = price * num;
            count++;
        }
        else
        {
            sale[flag].num += num;
            sale[flag].price += price * num;
        }

    }
}

int cmp(const void *a, const void *b)
{
    dish *first = (dish *) a;
    dish *second = (dish *) b;

    if (first -> price < second -> price)
        return -1;
    else if (first -> price > second -> price)
        return 1;
    else if (first -> num < second -> num)
        return -1;
    else if (first -> num > second -> num)
        return 1;
    else
        return 0;
}

void print()
{
    int result = 0;
    for (int i = 0; i < count; i++)
    {
        printf("%s %d %d\n", sale[i].code, sale[i].num, sale[i].price);
        result += sale[i].price;
    }

    printf("%d", result);
}
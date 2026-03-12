#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

char *str_combine(char *str1, char *str2);
int cmp(const void *a, const void *b);

int main(void)
{
    char str1[SIZE];char str2[SIZE];

    scanf("%s", str1);
    scanf("%s", str2); // 输入文本

    char *result = str_combine(str1, str2);

    printf("%s", result);

    free(result); // 释放内存
    return 0;
}

char *str_combine(char *str1, char *str2) // 字符串合并
{
    char *result = (char *) malloc (sizeof(char) * 2 * SIZE);
    int a = strlen(str1); int b = strlen(str2);

    for (int i = 0; i < a; i++)
        result[i] = str1[i];
    for (int j = 0; j < b; j++)
        result[a + j] = str2[j];
    
    result[a + b] = '\0';

    qsort(result, a + b, sizeof(char), cmp); // 按照大小排序

    return result;
}

int cmp(const void *a, const void *b) // 比较函数
{
    const char *first = (const char *)a;
    const char *second = (const char *)b;

    if (*first < *second)
        return -1;
    else if (*first > *second)
        return 1;
    else
        return 0;
}
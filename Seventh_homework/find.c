#include <stdio.h>
#include <string.h>

char words[3500][21]; // 存储单词表
int tail = 0;

void input(); // 从文件中读取单词
int ordersearch(char *word, int *flag); // 按顺序查词并输出对应查找次数
int halfsearch(char *word, int *flag); // 折半查词并输出对应的查找次数

int main(void)
{
    input();
    int method; int flag;
    int times;
    char input[21];

    scanf("%s %d", input, &method);

    if (method == 1)
        times = ordersearch(input, &flag);
    else if (method == 2)
        times = halfsearch(input, &flag);

    printf("%d %d", flag, times);
}

void input()
{
    FILE *fp = fopen("dictionary3000.txt", "r");

    char buffer[21];

    while (fgets(buffer, 21, fp) != NULL)
    {
        size_t n = strcspn(buffer, "\r\n");
        buffer[n] = '\0';
        strcpy(words[tail++], buffer);
    }
    
}

int ordersearch(char *word, int *flag)
{
    int result = 0;
    for (int i = 0; i < tail; i++)
    {
        result++;
        if (strcmp(word, words[i]) == 0)
        {
            *flag = 1;
            return result;
        }

        if (strcmp(word, words[i]) < 0)
        {
            *flag = 0;
            return result;
        }
    }

    *flag = 0;
    return result;
}

int halfsearch(char *word, int *flag)
{

    
}
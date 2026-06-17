#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NHASH  3001
#define MULT  37

char words[3500][21]; // 存储单词表
int tail = 0;
typedef struct vocab
{
    int start; // 记录每个字母单词的起始位置
    int num; // 储存对应数量
} vocab;
vocab table[26];
int rear = 0;

typedef struct hashunit
{
    char word[21];
    struct hashunit *next;
} hashunit;

hashunit *hashtable[3001] = {0}; // 哈希表

void init(); // 初始化单词表
void input(); // 从文件中读取单词 并且计入单词索引表
int ordersearch(char *word, int *flag); // 按顺序查词并输出对应查找次数
int halfsearch(char base[][21], int n, char *word, int *flag); // 折半查词并输出对应的查找次数
int indexsearch(char *word, int *flag); // 按照索引加折半查找并输出对应查找次数
int hashsearch(char *word, int *flag); // 按照哈希查找对应单词，并输出对应查找次数
unsigned int hash(char *str); // 哈希函数

int main(void)
{
    init();
    input();

    int method; int flag;
    int times;
    char input[21];

    scanf("%s %d", input, &method);

    if (method == 1)
        times = ordersearch(input, &flag);
    else if (method == 2)
        times = halfsearch(words, tail, input, &flag);
    else if (method == 3)
        times = indexsearch(input, &flag);
    else if (method == 4)
        times = hashsearch(input, &flag);

    printf("%d %d", flag, times);
}

void input()
{
    FILE *fp = fopen("dictionary3000.txt", "r");

    char buffer[21];

    char previous = '\0';

    int m = 0; // 计算每个字母开头的单词的数目

    while (fgets(buffer, 21, fp) != NULL)
    {
        size_t n = strcspn(buffer, "\r\n");
        buffer[n] = '\0';
        strcpy(words[tail], buffer);

        if (previous != buffer[0])
        {    
            if (previous != '\0')
                table[previous - 'a'].num = m;

            previous = buffer[0];
            table[buffer[0] - 'a'].start = tail;
            m = 0;
        }

        // 构建hash表
        int times = hash(buffer);
        hashunit *p = (hashunit *)malloc(sizeof(hashunit));
        strcpy(p -> word, buffer);
        p -> next = NULL;
        if (hashtable[times] == NULL)
        {
            hashtable[times] = p;
        }
        else
        {
            hashunit *temp = hashtable[times];

            if (strcmp(temp -> word, p -> word) > 0)
            {
                p -> next = temp;
                hashtable[times] = p;
            }
            else
            {
                while (temp -> next != NULL && strcmp(temp -> word, p -> word) < 0)
                    temp = temp -> next;

                temp -> next = p;
            }
        }
        
        m++;
        tail++;
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

int halfsearch(char base[][21], int n, char *word, int *flag)
{
    int low = 0;
    int high = n - 1;

    int result = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        result++;

        if (strcmp(word, base[mid]) == 0)
        {    
            *flag = 1;
            return result;
        }
        else if (strcmp(word, base[mid]) < 0)
            high = mid - 1;
        else 
            low = mid + 1;

    }

    *flag = 0;
    return result;
}

void init()
{
    for (int i = 0; i < 26; i++)
    {
        table[i].num = -1;
        table[i].start = -1;
    }

}

int indexsearch(char *word, int *flag)
{
    int location = table[word[0] - 'a'].start;
    int n = table[word[0] - 'a'].num;
    
    if (n == -1)
    {
        *flag = 0;
        return 0; //这个不算比较，这个只是看有没有这个元素
    }

    int times = halfsearch(&words[location], n, word, flag);

    return times;
}

unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;

    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    
    return h % NHASH;
}

int hashsearch(char *word, int *flag)
{
    hashunit *p = hashtable[hash(word)];
    int result = 0;

    while (p != NULL)
    {
        result++;
        if (strcmp(p -> word, word) == 0)
        {   
            *flag = 1; 
            return result;
        }
        else if (strcmp(p -> word, word) > 0)
        {    
            *flag = 0;
            return result;
        }

        p = p -> next;
    }


    *flag = 0;
    return result;
}
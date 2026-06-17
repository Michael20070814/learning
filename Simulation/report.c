#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LENGTH 500
#define SIZE 200

// 使用三个栈和一个队列来完成程序的编写 锁定直接按照顺序进入队列当中 清空队列后再弹出栈中元素

typedef struct Stack
{
    char things[LENGTH];
} Stack;

Stack A[SIZE];
Stack C[SIZE];
Stack B[SIZE];

typedef struct queue
{
    char Index[SIZE]; // 标记事件对应的类型
    char things[LENGTH][SIZE];
    int front;
    int rear;
} queue;

int a, b, c;

void init(); // 对栈进行初始化，其他的会因为全局变量自动初始化
void push(int flag, char *things); // 根据flag分流事件进入不同的栈
char* pop(int flag); // 根据flag分流返回不同栈的东西
int isStackEmpty(int flag); // 判断对应的栈是否为空
void push_queue(char *things, char index); // 推动事件进入队列 注意需要传入对应的组别
char *pop_queue(char *index); // 从队列当中弹出事件
int isQueueEmpty(); // 判断队列是否为空
void input(); // 从标准输入中读取事件
void lock(int num); // 锁定对应数量的新闻
void print(); // 把所有新闻进行输出

queue waiting;

int main(void)
{
    init();

    input();

    print();

    return 0;
}

void push(int flag, char *things)
{
    if (flag == 1)
    {
        strcpy(A[++a].things, things);
    }
    else if (flag == 2)
    {
        strcpy(B[++b].things, things);
    }
    else if (flag == 3)
    {
        strcpy(C[++c].things, things);
    }
}

char* pop(int flag)
{
    if (isStackEmpty(flag))
        return NULL;


    if (flag == 1)
    {
        return A[a--].things;
    }
    else if (flag == 2)
    {
        return B[b--].things;
    }
    else if (flag == 3)
    {
        return C[c--].things;
    }

    return NULL;
}

int isStackEmpty(int flag)
{
    if (flag == 1)
    {
        if (a == -1)
            return 1;
    }
    else if (flag == 2)
    {
        if (b == -1)
            return 1;
    }
    else if (flag == 3)
    {
        if (c == -1)
            return 1;
    }

    return 0;
}

void init()
{
    a = -1;
    b = -1;
    c = -1;
    waiting.front = waiting.rear = 0;
}

void push_queue(char *things, char index)
{
    strcpy(waiting.things[waiting.rear], things);
    waiting.Index[waiting.rear] = index;

    waiting.rear++;
}

char *pop_queue(char *index)
{
    if (isQueueEmpty())
        return NULL;

    *index = waiting.Index[waiting.front];
    return waiting.things[waiting.front++];
}

int isQueueEmpty()
{
    if (waiting.rear == waiting.front)
        return 1;

    return 0;
}

void input()
{
    char index;

    scanf("%c", &index);

    while (index != 'E')
    {
        getchar(); // 吃掉一个空格

        if (index == 'A' || index == 'B' || index == 'C')
        {   
            char buffer[LENGTH];
            fgets(buffer, LENGTH - 1, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            push(index - 'A' + 1, buffer);
        }
        else if (index == 'R')
        {
            int num;
            scanf("%d", &num);
            lock(num);
            getchar(); // scanf会读入一切字符，所以这里需要把换行符处理掉
        }
        else if (index == 'E')
            break;

        scanf("%c", &index);
    }
}

void lock(int num)
{
    int times = 0;
    char index;

    char *buffer;

    while (times != num)
    {
        if (!isStackEmpty(1))
        {    
            buffer = pop(1);
            times++;
            index = 'A';
        }
        else if (!isStackEmpty(2))
        {
            buffer = pop(2);
            times++;
            index = 'B';
        } 
        else if (!isStackEmpty(3))
        {
            buffer = pop(3);
            times++;
            index = 'C';
        }

        push_queue(buffer, index);
        
    }
}

void print()
{
    while (!isQueueEmpty())
    {
        char index;
        char *buffer = pop_queue(&index);
        printf("%c %s\n", index, buffer);
    }

    while (!isStackEmpty(1))
    {
        char *buffer = pop(1);
        printf("%c %s\n", 'A', buffer);
    }

    while (!isStackEmpty(2))
    {
        char *buffer = pop(2);
        printf("%c %s\n", 'B', buffer);
    }

    while (!isStackEmpty(3))
    {
        char *buffer = pop(3);
        printf("%c %s\n", 'C', buffer);
    }

}
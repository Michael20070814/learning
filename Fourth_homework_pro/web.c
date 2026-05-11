#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 150
#define MAXSIZE 100

typedef struct stack
{
    char obj[LENGTH][MAXSIZE];
    int top;
} stack;

// 队列作为已经输入了的网站
struct temp
{
    char web[LENGTH];
} InputWeb[MAXSIZE * 2];
int front = 0;
int rear = 0;

// 用来作为网站次数统计
typedef struct statistic
{
    char obj[LENGTH][MAXSIZE * 2];
    int times[MAXSIZE * 2];
    int location;
} statistic;

stack advance;
stack back;
statistic appearance;

void init();
int push_stack(char *input, int control);
int pop_stack(char *output, int control);
int push_queque(char *input);
void rollback(char *current);
void heading(char *current);
void print_web();
char *statistic_times(int *times);
char *extract_web(char *input);

int main(void)
{
    init();

    // 用于控制使用前进栈还是后退栈 前进栈是1 后退栈是2
    int Method = 0;

    char visit[] = "VISIT";
    char forward[] = ">>";
    char backward[] = "<<";
    char quit[] = "QUIT";

    char buffer[LENGTH];

    char CurrentWeb[LENGTH] = "https://www.baidu.com/";
    push_queque(CurrentWeb);

    // test0 测试init代码的有效性
    // init();
    // return 0;

    // test1 测试推入栈代码的有效性
    // push_stack("jiej", 1);
    // push_stack("ijifiej", 2);
    // return 0;

    // test2 测试入队代码有效性
    // push_queque("ijieji");

    // test3 测试能否回溯
    // push_stack("jiej", 1);
    // push_stack("ijifiej", 2);
    // rollback(CurrentWeb);
    // rollback(CurrentWeb);

    // test4 测试能否前进
    // push_stack("jiej", 1);
    // push_stack("ijifiej", 2);
    // heading(CurrentWeb);
    // heading(CurrentWeb);

    // test5 测试能否正常打印已进入的网址
    // push_queque("jifejij");
    // push_queque("feijifej");
    // print_web();

    // test6 测试能否正常提取网址
    // char *p = extract_web("https://www.baidu.com/");
    // printf("%s", p);
    // p = extract_web("https://www.buaa.edu.cn/bhgk/jrbh.htm");
    // printf("%s", p);

    // test7 测试能否正常统计信息
    // push_queque("https://www.buaa.edu.cn/");
    // push_queque("https://www.taobao.com/");
    // push_queque("https://www.buaa.edu.cn/jgsz/jxkyjg.htm");
    // int times24;
    // char *p24 = statistic_times(&times24);
    // print_web();
    // printf("%s %d", p24, times24);


    while (scanf("%s", buffer) == 1)
    {
        // 访问
        if (strcmp(buffer, visit) == 0)
        {
            Method = 2;
            char website[LENGTH];
            scanf("%s", website);
            size_t i = strcspn(website, "\n");
            website[i] = '\0';
            push_queque(website);
            push_stack(CurrentWeb, Method);
            strcpy(CurrentWeb, website);
            advance.top = -1;
        }
        else if (strcmp(buffer, forward) == 0) // 前进
        {
            heading(CurrentWeb);
        }
        else if (strcmp(buffer, backward) == 0) // 后退
        {
            rollback(CurrentWeb);
        }
        else if (strcmp(buffer, quit) == 0)
        {
            int input;
            scanf("%d", &input);
            if (input == 0)
            {
                int times;
                char *p = statistic_times(&times);
                print_web();
                printf("%s %d", p, times);

            }
            else if (input == 1)
            {
                print_web();
            }
        }
    }

    return 0;
}

// 初始化队列以及栈还有网站统计
void init()
{
    advance.top = -1;
    back.top = -1;
    appearance.location = -1;
}

// 入栈 错误返回0 成功返回1
int push_stack(char *input, int control)
{
    switch (control)
    {
        // 推入前进栈
        case 1:
        // 检验栈是否满
        if (advance.top == MAXSIZE - 1)
            return 0;
        
        strcpy(advance.obj[++advance.top], input);
        break;
        // 推入后退栈
        case 2:
        if (back.top == MAXSIZE - 1)
            return 0;

        strcpy(back.obj[++back.top], input);
        break;
    }

    return 1;
}

// 弹出栈
int pop_stack(char *output, int control)
{
    switch (control)
    {
        // 弹出前进栈
        case 1:
        // 检验栈是否为空
        if (advance.top == -1)
            return 0;
        
        strcpy(output, advance.obj[advance.top--]);
        break;
        // 弹出后退栈
        case 2:
        if (back.top == -1)
            return 0;

        strcpy(output, back.obj[back.top--]);
        break;
    }

    return 1;
}

// 往队列中推入字符串
int push_queque(char *input)
{
    // 检验队列是否已满
    if (rear == MAXSIZE * 2 + 1)
        return 0;

    strcpy(InputWeb[rear++].web, input);
    return 1;
}

void rollback(char *current)
{
    char buffer[LENGTH];
    if (pop_stack(buffer, 2) == 0)
        return ;
    
    push_stack(current, 1);
    strcpy(current, buffer);
    push_queque(current);
}

void heading(char *current)
{
    char buffer[LENGTH];

    if (pop_stack(buffer, 1) == 0)
        return ;

    push_stack(current, 2);
    strcpy(current, buffer);
    push_queque(current);
}

// 打印访问过的网址
void print_web()
{
    for (int i = front; i < rear; i++)
    {
        printf("%s\n", InputWeb[i].web);
    }
}

// 统计访问过的网址以及对应访问次数
char *statistic_times(int *times)
{
    int flag; int i;
    int maxtimes; int index;

    for (int i = front; i < rear; i++)
    {
        flag = 0;
        int m;
        char *p = extract_web(InputWeb[i].web);
        // 查看是否已经有对应的网址
        for (m = 0; m <= appearance.location; m++)
        {
            if (strcmp(appearance.obj[m], p) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            appearance.times[m]++;
        }
        else if (flag == 0)
        {
            strcpy(appearance.obj[++appearance.location], p);
            appearance.times[appearance.location] = 1;
        }
        free(p);
    }

    maxtimes = appearance.times[0];
    index = 0;
    for (i = 0; i <= appearance.location; i++)
    {
        if (appearance.times[i] > maxtimes)
        {
            maxtimes = appearance.times[i];
            index = i;
        }
    }

    *times = maxtimes;
    return appearance.obj[index];
}

// 提取网页名字
char *extract_web(char *input)
{
    char *p = input;
    char *front;
    char *rear;
    char *result = (char *) malloc(sizeof(char) * LENGTH);

    while (*p != '\0')
    {
        // 迅速移动到我们所需要的位置
        if (*p == '/' && *(p + 1) == '/')
        {    
            p = p + 2;
            front = p;
            continue;
        }
        else if (*p == '/')
        {
            rear = p;
            break;
        }
        p++;
    }

    for (char *iter = front; iter < rear; iter++)
    {
        result[iter - front] = *iter;
    }
    result[rear - front] = '\0';

    return result;
}
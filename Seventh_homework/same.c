#include <stdio.h>
#include <stdlib.h>
#define num 200

typedef struct Base
{
    long long number[num];
    int enter_time[num];
    int quit_time[num];
    int tail;
} Base; // 按照基站记入信息

typedef struct result
{
    long long number;
    char name; // 存储基站的名字
} result; // 存储输出的结果

Base station[6]; // 总共六个基站

result object[num]; // 输出的基站
int rear = 0; // 标记最后结果所在的位置

void init(); // 对基站进行初始化
void input(); // 读取输入
void scan(); // 扫描数据库，找出有重叠的电话号码
void storebase(int basis, long long number, int start, int end); // 根据对应的手机号和基站的重叠开一个新的数组用于输出
int judge_in(int telestart, int teleend, int start, int end); // 根据标准手机号和遍历手机号的进入和推出时间返回是否存在重合部分
void output(); // 整体输出 额外新开一个
int cmp(const void *a, const void *b); // 比较函数 用于手机号排序
int notExist(long long telenum, char c); // 判断是否读入重复的手机号与基站

int main(void)
{
    init();

    input();

    scan();

    qsort(object, rear, sizeof(result), cmp);

    output();

    return 0;
}

void init()
{
    for (int i = 0; i < 6; i++)
    {
        station[i].tail = 0;
    }
}

void input()
{
    int input_num;
    scanf("%d", &input_num);

    for (int m = 0; m < input_num; m++)
    {
        long long telenum;
        char base_name;
        int start_time;
        int end_time;

        scanf("%lld %c %d%d", &telenum, &base_name, &start_time, &end_time);

        station[base_name - 'A'].number[station[base_name - 'A'].tail] = telenum;
        station[base_name - 'A'].enter_time[station[base_name - 'A'].tail] = start_time;
        station[base_name - 'A'].quit_time[station[base_name - 'A'].tail] = end_time;
        station[base_name - 'A'].tail++;
    }
}

void scan()
{
    long long telenum;

    scanf("%lld", &telenum);

    for (int i = 0; i < 6; i++)
    {
        for (int m = 0; m < station[i].tail; m++)
        {
            if (station[i].number[m] == telenum)
                storebase(i, telenum, station[i].enter_time[m], station[i].quit_time[m]);
        }
    }
}

void storebase(int basis, long long number, int start, int end)
{
    for (int m = 0; m < station[basis].tail; m++)
    {
        if (station[basis].number[m] != number)
        {
            if (judge_in(station[basis].enter_time[m], station[basis].quit_time[m], start, end))
            {
                if (notExist(station[basis].number[m], basis + 'A'))
                {     
                    object[rear].number = station[basis].number[m];
                    object[rear++].name = basis + 'A';
                }
            }
        }
    }
}

int judge_in(int telestart, int teleend, int start, int end)
{
    if (telestart <= start && teleend >= start)
        return 1;
    else if (telestart <= end && teleend >= start)
        return 1;
    else
        return 0;
}

void output()
{
    for (int i = 0 ; i < rear; i++)
    {
        printf("%lld %c\n", object[i].number, object[i].name);
    }
}

int cmp(const void *a, const void *b)
{
    result *first = (result *) a;
    result *second = (result *) b;

    if (first -> number < second -> number)
        return -1;
    else if (first -> number > second -> number)
        return 1;
    else if (first -> name < second -> name)
        return -1;
    else if (first -> name > second -> name)
        return 1;
    else
        return 0;
}

int notExist(long long telenum, char c)
{
    for (int i = 0; i < rear; i++)
    {
        if (object[i].name == c && object[i].number == telenum)
            return 0;
    }

    return 1;
}
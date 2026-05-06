#include <stdio.h>
#define MAXSIZE 1000
#define WIN_NUM 5

// 记录进入的乘客
typedef struct Queue
{
    int data[MAXSIZE];
    int front;
    int rear;
    int waitingTime[MAXSIZE];
} Queue;

typedef struct Windows
{
    int remaining;
    int Free;
    int type;
    // 1 表示对私 2 表示对公 3 表示外币
} Windows;

// 五个服务窗口
Windows Worker[5];

void initWindows();
void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
int push(Queue *q, int x);
int pop(Queue *q, int *x);
int getFront(Queue *q, int *x);
int size(Queue *q);
void ServeClient(Queue *q);
void AdjustWindows(Queue *q, int flag);
void print(Queue q);
void CycleRunning(Queue *q);
int FetchWin();
int IsThereFreeWin();

int main(void)
{
    int cycle; 
    int flag = 1;
    Queue Client;

    initQueue(&Client);
    initWindows();

    scanf("%d", &cycle);

    int client_num[cycle];

    // 获取每一个周期用户数量
    for (int i = 0; i < cycle; i++)
        scanf("%d", client_num + i);

    for (int i = 0; i < cycle; i++)
    {
        flag = 1;
        for (int m = 0; m < client_num[i]; m++)
        {
            int temp;
            scanf("%d", &temp);
            push(&Client, temp);
        }
        AdjustWindows(&Client, flag);

        flag = 0;
        while (IsThereFreeWin() && !isEmpty(&Client)) 
            ServeClient(&Client);

        
        AdjustWindows(&Client, flag);
        
        CycleRunning(&Client);
    }

    flag = 0;
    while (!isEmpty(&Client))
    {
        while (IsThereFreeWin() && !isEmpty(&Client))
            ServeClient(&Client);

        AdjustWindows(&Client, flag);
        CycleRunning(&Client);
    }

    print(Client);

    return 0;
}

void initQueue(Queue *q)
{
    q -> front = 0;
    q -> rear = 0;
    for (int i = 0; i < MAXSIZE; i++)
    {
        q -> waitingTime[i] = 0;
    }
}

int isEmpty(Queue *q)
{
    if (q -> front == q -> rear)
        return 1;
    else
        return 0;
}

int isFull(Queue *q)
{
    if (q -> rear == MAXSIZE)
        return 1;
    else
        return 0;
}

int push(Queue *q, int x)
{
    if (isFull(q))
        return 0;
    
    q -> data[q -> rear] = x;
    q -> rear = q -> rear + 1;

    return 1;
}

int pop(Queue *q, int *x)
{
    if (isEmpty(q))
        return 0;

    *x = q -> data[q -> front];
    q -> front = q -> front + 1;

    return 1;
}

int getFront(Queue *q, int *x)
{
    if (isEmpty(q))
        return 0;
    
    *x = q -> data[q -> front];

    return 1;
}

int size(Queue *q)
{
    return q -> rear - q -> front;
}

void initWindows()
{
    for (int j = 0; j < WIN_NUM; j++)
    {
        Worker[j].Free = 1;
        Worker[j].remaining = 0;
        if (j < 3)
            Worker[j].type = 1;
        else if (j == 3)
            Worker[j].type = 2;
        else if (j == 4)
            Worker[j].type = 3;
    }
}

// 给客户分配窗口（若有）
void ServeClient(Queue *q)
{
    int time;

    if (!getFront(q, &time))
        return ;

    for (int j = 0; j < WIN_NUM; j++)
    {
        if (Worker[j].Free == 1 && Worker[j].type == 1)
        {
            pop(q, &time);
            Worker[j].Free = 0;
            Worker[j].remaining = time;
            return ;
        }
    }
}

void AdjustWindows(Queue *q, int flag)
{
    int num = FetchWin();

    int AverageWaiting = size(q) / num;

    // 检测是否需要增添窗口
    if (AverageWaiting >= 7 && flag == 1)
    {
        for (int i = 0; i < WIN_NUM; i++)
        {
            if (Worker[i].type != 1)                
            {
                Worker[i].type = 1;
                if (size(q) / (num + 1) >= 7 && i == 3)
                    Worker[i + 1].type = 1;
                break;
            }
        }
    }

    // 检测是否需要减少窗口
    if (num > 3)
    {
        if (AverageWaiting < 7)
        {
            for (int j = WIN_NUM - 1; j > WIN_NUM - 3; j--)
            {
                if (Worker[j].type == 1)
                {
                    Worker[j].type = j - 1;
                    if (size(q) / (num - 1) < 7 && j == 4)
                        Worker[j - 1].type = j - 2;
                    return ;
                }
            }
        }
    }

}

// 获取现在的对私服务窗口数目
int FetchWin()
{
    int result = 0;
    for (int i = 0; i < WIN_NUM; i++)
    {
        if (Worker[i].type == 1)
            result++;
    }
    return result;
}

void print(Queue q)
{
    for (int i = 0; i < q.front; i++)
        printf("%d : %d\n", i + 1, q.waitingTime[i]);
}

void CycleRunning(Queue *q)
{
    // 增加等待时长
    for (int i = q -> front; i < q -> rear; i++)
        q -> waitingTime[i]++;
    
    // 每一个柜台都处理一下
    for (int i = 0; i < WIN_NUM; i++)
    {
        if (Worker[i].remaining > 0)
            Worker[i].remaining--;
        
        if (Worker[i].remaining == 0 && Worker[i].Free == 0)
            Worker[i].Free = 1;
    }
}

int IsThereFreeWin()
{
    for (int i = 0; i < WIN_NUM; i++)
    {
        if (Worker[i].Free == 1 && Worker[i].type == 1)
            return 1;
    }

    return 0;
}
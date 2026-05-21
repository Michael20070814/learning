#include <stdio.h>
#include <string.h>
#define MAXSIZE 50

typedef struct Location
{
    char SpotName[MAXSIZE];
    int distance;
} Location;

typedef struct buffer
{
    int index[MAXSIZE];
    char SpotName[MAXSIZE][MAXSIZE];
    int top;
} buffer;

buffer C;
buffer B;
buffer A;
int push;

void init(); // 用于初始化栈
// 不能把全局变量
void origin_push(int index, char *input, buffer *obj); // 用于最基本的入栈
void pop(int *index, char *input, buffer *obj); // 用于弹出栈
int isEmpty(buffer *src); // 用于检验是否为空
int isFull(buffer *src); // 用于检验是否已满
int FindNearest(buffer src, Location *destination, int number); // 用于查找最近的地点在哪里
void pushBtoA(int reverse); // 把B的最上层推入A
void pushAtoC(int reverse); // 把A的最上层推入C 可以反转 // 为0时不反转 为1时反转
void print(); // 打印车厢编号以及push次数

int main(void)
{
    init();

    int LocationNum;
    scanf("%d", &LocationNum);

    Location destination[LocationNum];

    for (int num = 0; num < LocationNum; num++)
    {
        scanf("%s", destination[num].SpotName);
        scanf("%d", &destination[num].distance);
    }

    int CarriageNum;
    scanf("%d", &CarriageNum);

    for (int num = 0; num < CarriageNum; num++)
    {
        int index; char input[MAXSIZE];

        scanf("%d %s", &index, input);
        origin_push(index, input, &A);
    }

    for (int num = 0; num < CarriageNum; num++)
    {
        pushBtoA(1);
    }

    while (!isEmpty(&B))
    {
        int index = FindNearest(B, destination, LocationNum);

        int length = B.top;

        for (int num = length; num >= index; num--)
        {
            pushBtoA(0);
        }

        if (index == length)
            continue;
        else
        {
            pushAtoC(0);
            for (int num = length; num > index; num--)
            {
                pushBtoA(1);
            }
            pushAtoC(1);
        }
    }

    print();

    // test0 测试初始化
    // init();

    // // test1 测试能否正常push
    // int index = 2;
    // char input[] = "Hello";
    // origin_push(index, input, &A);

    // // test2 测试能否正常弹出
    // int al;
    // char output[MAXSIZE];
    // pop(&al, output, &A);

    // test3 测试能否找到正确位置
    // int LocationNum;
    // scanf("%d", &LocationNum);

    // Location destination[LocationNum];

    // for (int num = 0; num < LocationNum; num++)
    // {
    //     scanf("%s", destination[num].SpotName);
    //     scanf("%d", &destination[num].distance);
    // }

    // int CarriageNum;
    // scanf("%d", &CarriageNum);

    // for (int num = 0; num < CarriageNum; num++)
    // {
    //     int index; char input[MAXSIZE];

    //     scanf("%d %s", &index, input);
    //     origin_push(index, input, &A);
    // }
    // int x = FindNearest(A, destination, LocationNum);

    // test4 测试能否正常打印输出
    // print();


    return 0;
}

void init()
{
    A.top = -1;
    B.top = -1;
    C.top = -1;
    push = 0;
}

void origin_push(int index, char *input, buffer *obj) // num = 1 A; num = 2 B; num = 3 C
{
    if (isFull(obj))
        return ;

    obj->top++;
    obj->index[obj->top] = index;
    strcpy(obj->SpotName[obj->top], input);
    
}

void pop(int *index, char *input, buffer *obj)
{
    if (isEmpty(obj))
        return ;

    
    *index = obj->index[obj->top];
    strcpy(input, obj->SpotName[obj->top]);
    obj->top--;
}

int isEmpty(buffer *src)
{
    if (src->top == -1)
        return 1;
    
    return 0;
}

int isFull(buffer *src)
{
    if (src->top == 49)
        return 1;

    return 0;
}

int FindNearest(buffer src, Location *destination, int number)
{
    int i;

    for (int num = number - 1; num >= 0; num--)
    {
        int flag = 0;
        for (i = src.top; i >= 0; i--)
            if (strcmp(destination[num].SpotName, src.SpotName[i]) == 0)
            {
                flag = 1;
                break;
            }

        if (flag == 1)
            break;
    }

    return i;
}

void pushBtoA(int reverse)
{
    if (reverse == 0)
    {
        int index;
        char input[MAXSIZE];
        pop(&index, input, &B);
        origin_push(index, input, &A);
        push++;
    }
    else if (reverse == 1)
    {
        int index;
        char input[MAXSIZE];
        pop(&index, input, &A);
        origin_push(index, input, &B);
    }
}

void pushAtoC(int reverse)
{
    if (reverse == 0)
    {
        int index;
        char input[MAXSIZE];
        pop(&index, input, &A);
        origin_push(index, input, &C);
    }
    else if (reverse == 1)
    {
        int index;
        char input[MAXSIZE];
        pop(&index, input, &C);
        origin_push(index, input, &A);
        push++;
    }
}

void print()
{
    for (int i = 0; i < A.top; i++)
    {
        printf("%04d ", A.index[i]);
    }

    printf("%04d\n", A.index[A.top]);
    printf("%d", push);

}
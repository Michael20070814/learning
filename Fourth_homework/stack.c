#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct Stack
{
    int data[MAXSIZE];
    int top;
} Stack;

Stack Over;

void init();
int isEmpty();
int isFull();
int push(int x);
int pop();

int main(void)
{
    int input;
    scanf("%d", &input);

    init();

    while (input != -1)
    {
        int temp;

        switch (input)
        {
            case 1:
            scanf("%d", &temp);
            push(temp);
            case 0:
            pop();
            break;
            case -1:
            break;
        }
        if (input == -1)
            break;
        scanf("%d", &input);
    }

    return 0;
}

void init()
{
    Over.top = -1;
}

int isEmpty()
{
    if (Over.top == -1)
        return 1;
    else
        return 0;
}

int isFull()
{
    if (Over.top == MAXSIZE - 1)
        return 1;
    else
        return 0;
}

int push(int x)
{
    if (isFull())
    {
        printf("error ");
        return 0;
    }

    Over.data[++Over.top] = x;
    return 1;
}

int pop()
{
    if (isEmpty())
    {
        printf("error ");
        return 0;
    }

    printf("%d ", Over.data[Over.top--]);
    return 1;
}
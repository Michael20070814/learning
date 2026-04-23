#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define LENGTH 50

typedef struct Stack
{
    int operand;
    int location;
    char string[LENGTH];
    int top;
} Stack;

Stack String;

void init();
int isEmpty();
int isFull();
int push(int x);
int pop();





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
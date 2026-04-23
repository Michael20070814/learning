#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 500

typedef struct Stack
{
    float data[MAXSIZE];
    int top;
} Stack;

void init(Stack *input);
int isEmpty(Stack input);
int isFull(Stack input);
int push(Stack *input, float x);
float pop(Stack *input);
int isOperator(char operator);
int precedence(Stack Operator, char cur);
void calc(Stack *Value, int oper);
int getStack(Stack input);

int main(void)
{
    Stack Operator;
    Stack Value;
    init(&Operator);
    init(&Value);
    char input[MAXSIZE];
    int num = 0;

    fgets(input, MAXSIZE - 1, stdin);
    while (input[num] != '=')
    {
        if (input[num] == ' ')
        {   
            num++; 
            continue;
        }

        if (isdigit(input[num]))
        {
            float temp = 0;
            while (isdigit(input[num]))
                temp = temp * 10 + (input[num++] - '0');
            
            push(&Value, temp);
        }

        if (isOperator(input[num]))
        {
            if (isEmpty(Operator))
                push(&Operator, input[num]);
            else
            {
                while (precedence(Operator, input[num]))
                {    
                    int oper;
                    oper = pop(&Operator);
                    calc(&Value, oper);
                    // pop完要检验是否为0
                    if (isEmpty(Operator))
                        break;
                }
                push(&Operator, input[num]);
            }
            num++;
        }

        if (input[num] == '(')
        {    
            push(&Operator, '(');
            num++;
        }

        if (input[num] == ')')
        {
            int oper;
            while ((oper = pop(&Operator)) != '(')
                calc(&Value, oper);
            
            num++;
        }
    }

    while (!isEmpty(Operator))
    {
        int oper;
        oper = pop(&Operator);
        calc(&Value, oper);
    }

    printf("%.2f", pop(&Value));

    return 0;
}

void init(Stack *input)
{
    input -> top = -1;
}

int isEmpty(Stack input)
{
    if (input.top == -1)
        return 1;
    else
        return 0;
}

int isFull(Stack input)
{
    if (input.top == MAXSIZE - 1)
        return 1;
    else
        return 0;
}

int push(Stack *input, float x)
{
    if (isFull(*input))
    {
        printf("error ");
        return 0;
    }

    input -> top++;
    input -> data[input -> top] = x;
    
    return 1;
}

float pop(Stack *input)
{
    if (isEmpty(*input))
    {
        printf("error ");
        return 0;
    }

    return input -> data[input -> top--];
}

int isOperator(char operator)
{
    if (operator == '+' || operator == '-' ||
        operator == '/' || operator == '*')
        return 1;
    
    return 0;
}

int precedence(Stack Operator, char cur)
{
    int top = getStack(Operator);

    if (top == '(')
        return 0;

    if (cur == '-' || cur == '+')
        return 1;

    if (top == '*' || top == '/')
        return 1;

    return 0;
}

int getStack(Stack input)
{
    return input.data[input.top];
}

void calc(Stack *Value, int oper)
{
    float operand2 = pop(Value);
    float operand1 = pop(Value);

    switch (oper)
    {
        case '+':
        push(Value, operand1 + operand2);
        break;
        case '-':
        push(Value, operand1 - operand2);
        break;
        case '*':
        push(Value, operand1 * operand2);
        break;
        case '/':
        push(Value, operand1 / operand2);
        break;
    }
}
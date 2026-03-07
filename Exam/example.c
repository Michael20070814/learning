#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define OP_SUM -1
#define OP_SUB -2
#define OP_MUL -3
#define OP_DIV -4

void delete_space(char *s)
{
    char *p = s;
    int index = 0;
    while (*p != '\0')
    {
        if (isspace(*p))
        {
            p++;
            continue;
        }
        else
        {
            s[index] = *p;
            index++;
            p++;
        }
    }
    s[index] = '\0';
}

int get_priority(char s)
{
    switch (s)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int *shunting_yard(char *s, int *size)
{
    char *p = s;
    int index = 0;
    char operator[500];
    int *output = (int *)malloc(sizeof(int) * 1000);
    int output_index = 0;int operator_index = -1;
    while (s[index] != '\0')
    {
        if (output_index > 0 && isdigit(s[index - 1]) && isdigit(s[index]))
        {
            output[output_index - 1] = output[output_index - 1] * 10 + s[index] - '0';
        }
        else if (isdigit(s[index]) && (output_index == 0 || (!isdigit(s[index - 1]))))
        {
            output[output_index++] = s[index] - '0';
        }
        else if (s[index] == '(')
        {
            operator[++operator_index] = *p;
        }
        else if (s[index] == ')')
        {
            while (operator[operator_index] != '(')
            {
                if (operator[operator_index] == '+') output[output_index] = OP_SUM;
                else if (operator[operator_index] == '-') output[output_index] = OP_SUB;
                else if (operator[operator_index] == '*') output[output_index] = OP_MUL;
                else if (operator[operator_index] == '/') output[output_index] = OP_DIV;
                output_index++;
                operator_index--;
            }
        }
        else if (s[index] == '+' || s[index] == '-' || s[index] == '*' || s[index] == '/')
        {
            while (operator_index > -1 && get_priority(operator[operator_index]) >= get_priority(s[index]))
            {
                char op = operator[operator_index--];
                if (op == '+') output[output_index++] = OP_SUM;
                else if (op == '-') output[output_index++] = OP_SUB;
                else if (op == '*') output[output_index++] = OP_MUL;
                else if (op == '/') output[output_index++] = OP_DIV;
            }
            operator[++operator_index] = s[index];
        }
        index++;
    }
    while (operator_index > -1)
    {
        char op = operator[operator_index--];
        if (op == '+') output[output_index++] = OP_SUM;
        else if (op == '-') output[output_index++] = OP_SUB;
        else if (op == '*') output[output_index++] = OP_MUL;
        else if (op == '/') output[output_index++] = OP_DIV;
    }
    
    *size = output_index;

    return output;
}

int calculate(int *s, int size)
{
    int result[100];int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (s[i] >= 0)
            result[index++] = s[i];
        else if (s[i] == OP_MUL)
        {
            int temp = result[index - 1] * result[index - 2];
            index = index - 2;
            result[index++] = temp;
        }
        else if (s[i] == OP_SUM)
        {
            int temp = result[index - 1] + result[index - 2];
            index = index - 2;
            result[index++] = temp;
        }
        else if (s[i] == OP_SUB)
        {
            int temp = result[index - 2] - result[index - 1];
            index = index - 2;
            result[index++] = temp;
        }
        else if (s[i] == OP_DIV)
        {
            int temp = result[index - 2] / result[index - 1];
            index = index - 2;
            result[index++] = temp;
        }
    }
    return result[0];
}

int main(void)
{
    char s[2000];
    int size;
    
    if (fgets(s, 1999, stdin) == NULL)
        return 0;
    
    delete_space(s);

    int *yard = shunting_yard(s, &size);

    int result = calculate(yard, size);

    printf("%d", result);

    return 0;
}
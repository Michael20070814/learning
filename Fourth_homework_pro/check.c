#include <stdio.h>
#define SIZE 500

void init();
int isEmpty();
int isFull();
int push(int x, int line);
int pop();
int getTop();
int search(int c);

struct 
{
    int data[SIZE];
    int Line[SIZE];
    int top;
} Bracket;

int main(void)
{
    FILE *fp = fopen("example.c", "r");

    int c, next;
    int line = 1;
    int index = 0;
    int in_string = 0;
    int in_char = 0;
    int in_comment = 0;
    int error = 0;

    char result[SIZE];

    init();

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
            line++;

        // When encounter character such as //, */, ", you should reset the status
        if (in_comment == 1)
        {
            if (c == '\n')
            {    
                in_comment = 0;
            }
            continue;
        }
        else if (in_comment == 2)
        {
            if (c == '*')
            {
                next = fgetc(fp);
                if (next == '/')
                    in_comment = 0;
                else
                    ungetc(next, fp);
            }
            continue;
        }
        else if (in_string == 1)
        {
            if (c == '"')
                in_string = 0;
        }
        else if (in_char == 1)
        {
            if (c == '\'')
                in_char = 0;
        }
        else
        {
            if (c == '/')
            {
                next = fgetc(fp);
                if (next == '/')
                    in_comment = 1;
                else if (next == '*')
                    in_comment = 2;
                else
                    ungetc(next, fp);
            }
            else if (c == '\'')
                in_char = 1;
            else if (c == '"')
                in_string = 1;
            else
            {
                if (c == '{')
                {    
                    if (getTop() == '(')
                    {
                        error = 1;
                        c = '(';
                        break;
                    }
                    push(c, line);
                    result[index++] = c;
                }
                else if (c == '}')
                {
                    if (getTop() == '{')
                    {   
                        result[index++] = c; 
                        pop();
                    }
                    else
                    {
                        error = 1;
                        break;
                    }
                }
                else if (c == '(')
                {
                    push(c, line);
                    result[index++] = c;
                }
                else if (c == ')')
                {
                    if (getTop() == '(')
                    {    
                        result[index++] = c;
                        pop();
                    }
                    else
                    {
                        error = 1;
                        break;
                    }
                }
                
            }
        }
    }

    int temp;
    result[index] = '\0';

    if (!isEmpty())
        error = 1;

    if (error == 1)
    {
        if ((temp = search(c)))
            printf("without maching '%c' at line %d\n", Bracket.data[Bracket.top], temp);
        else
            printf("without maching '%c' at line %d\n", c, line);
    }
    else
        printf("%s", result);
    
    return 0;
}

void init()
{
    Bracket.top = -1;
}

int isEmpty()
{
    if (Bracket.top == -1)
        return 1;
    else
        return 0;
}
// chect if it's full
int isFull()
{
    if (Bracket.top == SIZE - 1)
        return 1;
    else
        return 0;
}
// push the top
int push(int x, int line)
{
    if (isFull())
    {
        return 0;
    }

    Bracket.top++;
    Bracket.data[Bracket.top] = x;
    Bracket.Line[Bracket.top] = line;

    return 1;
}
// return the top's line of dump, and pop it out
int pop()
{
    if (isEmpty())
    {
        return 0;
    }

    return Bracket.Line[Bracket.top--];
}
// return the top of dump without pop it
int getTop()
{
    if (isEmpty())
    {
        
        return 0;
    }

    return Bracket.data[Bracket.top];
}

int search(int c)
{
    if (c == -1)
        return Bracket.Line[Bracket.top];

    for (int m = 0; m <= Bracket.top; m++)
    {
        if (c == Bracket.data[m])
            return Bracket.Line[m];
    }
    return 0;
}
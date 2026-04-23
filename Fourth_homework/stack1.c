#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXSIZE 500
#define LENGTH 50

typedef struct Call
{
    char function[LENGTH];
    char BeCalledFunc[MAXSIZE][LENGTH];
    int num;
} Call;

Call func[MAXSIZE];
int number;

typedef struct Stack
{
    char data[MAXSIZE][LENGTH];
    int top;
} Stack;

void init(Stack *input);
int isEmpty(Stack input);
int isFull(Stack input);
int push(Stack *input, char *x);
char *pop(Stack *input);
char *getlast(Stack *input);
int Add(char *before, char *x);
int Register(char *x);
int print();
void replace_n(char *input);

int main(void)
{
    Stack Program;
    init(&Program);
    memset(func, 0, sizeof(func));
    number = 0;

    int num; char temp[LENGTH];
    scanf("%d", &num);
    scanf("%s", temp);
    replace_n(temp);    
    push(&Program, temp);
    Register(temp);

    while (!isEmpty(Program))
    {
        scanf("%d", &num);
        if (num == 8)
        {    
            scanf("%s", temp);
            push(&Program, temp);
            replace_n(temp);
            for (int num = 0; num < Program.top; num++)
            {
                char *FuncName = getlast(&Program);
                Add(FuncName, temp);
            }
            Register(temp);
        }
        else if (num == 0)
        {
            pop(&Program);
        }
    }

    print();

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

int push(Stack *input, char *x)
{
    if (isFull(*input))
    {
        printf("error ");
        return 0;
    }

    input -> top++;
    strcpy(input -> data[input -> top], x);
    
    return 1;
}

char *pop(Stack *input)
{
    if (isEmpty(*input))
    {
        printf("error ");
        return 0;
    }

    return input -> data[input -> top--];
}

char *getlast(Stack *input)
{
    int m = input->top;
    return input->data[m - 1];
}

int Add(char *before, char *x)
{
    for (int m = 0; m < number; m++)
    {
        if(!strcmp(before, func[m].function))
        {
            for (int n = 0; n < func[m].num; n++)
            {
                if (!strcmp(x, func[m].BeCalledFunc[n]))
                    return 0;
            }
            strcpy(func[m].BeCalledFunc[func[m].num], x);
            func[m].num++;
            return 1;
        }
    }

    return 1;
}

int Register(char *x)
{
    strcpy(func[number].function, x);
    number++;

    return 1;
}

int print()
{
    for (int m = 0; m < number; m++)
    {
        if (func[m].num != 0)
        {
            char buffer[MAXSIZE];
            sprintf(buffer, "%s:", func[m].function);
            printf(buffer);
            for (int i = 0; i < func[m].num; i++)
            {    
                printf("%s", func[m].BeCalledFunc[i]);
                if (i + 1 != func[m].num)
                    printf(",");
            }
            printf("\n");
        }
    }
    return 1;
}

void replace_n(char *input)
{
    size_t n = strcspn(input, "\n");
    input[n] = '\0';
}
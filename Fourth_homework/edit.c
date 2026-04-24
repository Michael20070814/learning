#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 512
#define MAXSIZE 100
#define LENGTH 50

typedef struct Operand
{
    int operand;
    int location;
    char string[SIZE];
} Operand;

typedef struct Stack
{
    Operand Doing[MAXSIZE];
    int top;
} Stack;

Stack String;
char Str[SIZE];

void init();
int isEmpty();
int isFull();
int push(char *input);
int pop();
void record();
void replace_n(char *input);

int main(void)
{
    init();
    memset(Str, 0, sizeof(char) * SIZE);

    fgets(Str, SIZE - 1, stdin);
    replace_n(Str);

    // char temp[LENGTH];

    // fgets(temp, LENGTH - 1, stdin);
    // replace_n(temp);
    // push(temp);
    // pop();

    record();

    int num ;
    char buffer[SIZE];
    fgets(buffer, SIZE - 1, stdin);
    sscanf(buffer, "%d", &num);

    while (num != -1) 
    {
        switch (num)
        {
            case 3:
            pop();
            break;
            case 2:
            case 1:
            push(buffer);
            break;
        }
        fgets(buffer, SIZE - 1, stdin);
        sscanf(buffer, "%d", &num);
    }

    printf("%s", Str);

    return 0;
}

void init()
{
    String.top = -1;
}

int isEmpty()
{
    if (String.top == -1)
        return 1;
    else
        return 0;
}

int isFull()
{
    if (String.top == MAXSIZE - 1)
        return 1;
    else
        return 0;
}

int push(char *input)
{
    int operand; int location; int n;
    char content[SIZE];

    if (isFull())
    {
        printf("error ");
        return 0;
    }

    sscanf(input, "%d", &operand);
    
    if (operand == 1)
    {
        sscanf(input, "%d %d %s", &operand, &location, content);
        int L = strlen(content);
        int length = strlen(Str) - location + 1;

        memmove(&Str[location + L], &Str[location], length + 1);
        strncpy(&Str[location], content, L);
    }
    else if (operand == 2)
    {
        sscanf(input, "%d %d %d", &operand, &location, &n);
        int L = strlen(Str);

        strncpy(content, &Str[location], n);
        content[n] = '\0';
        int length = L - location - n + 1;
        if (location + n < L)
            memmove(&Str[location], &Str[location + n], length + 1);
        else
            Str[location] = '\0';
    }
    
    String.top++;
    String.Doing[String.top].operand = operand;
    String.Doing[String.top].location = location;
    strcpy(String.Doing[String.top].string, content);

    return 1;
}

int pop()
{
    if (isEmpty())
    {
        printf("error ");
        return 0;
    }

    // Parse
    int operand = String.Doing[String.top].operand;
    if (operand == 1)
    {
        int n = String.Doing[String.top].location;
        int length = strlen(String.Doing[String.top].string);

        int L = strlen(Str) - n - length + 1;
        memmove(&Str[n], &Str[n + length], L + 1);
    }
    else if(operand == 2)
    {
        int n = String.Doing[String.top].location;
        int length = strlen(String.Doing[String.top].string);
        int L = strlen(Str) - n + 1;
        memmove(&Str[n + length], &Str[n], L + 1);
        strncpy(&Str[n], String.Doing[String.top].string, length);
    }

    String.top--;
    return 1;
}

void record()
{
    int num ;
    int operand; int location; char content[SIZE];
    char buffer[SIZE * 2];

    scanf("%d", &num);
    // remove the \n
    getchar();

    for (int m = 0; m < num; m++)
    {
        String.top++;
        fgets(buffer, SIZE - 1, stdin);
        sscanf(buffer, "%d %d %s", &operand, &location, content);
        size_t n = strcspn(content, "\n");
        content[n] = '\0';

        String.Doing[String.top].location = location;
        String.Doing[String.top].operand = operand;
        strcpy(String.Doing[String.top].string, content);
    }
}

void replace_n(char *input)
{
    size_t n = strcspn(input, "\n");
    input[n] = '\0';
}

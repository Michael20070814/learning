#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE 200
#define NUM 32

int cmp(const void *a, const void *b);
int judge_overlap(char src[][SIZE], char *obj, int m);
int isdefaultword(char *token);

const char *keywords[] = 
{
    "int", "if", "else", "for", "while", "do", "return",
    "main", "void", "char", "float", "double", "switch", 
    "case", "break", "continue", "default", "fopen",
    "fgets", "strlen", "memset", "isalpha",
    "goto", "static", "sizeof", "short", 
    "const", "enum", "long", "register", 
    "struct", "switch", "typedef", "union", "unsigned", 
    "malloc", "NULL", "printf", "scanf", NULL
};

int main(void)
{
    char head[SIZE];
    fgets(head, SIZE, stdin);


    int Len = strlen(head);
    char temp[NUM][SIZE];
    memset(temp, 0, NUM * SIZE * sizeof(char));
    int n = 0; int i = 0;
    int flag = 0;

    for (int h = 0; h < Len; h++)
    {
        if (flag == 1)
        {
            flag = 0;
            i = 0;
            n++;
        }

        if ((isalpha(head[h]) || head[h] == '_' || (isdigit(head[h]) && i != 0)) 
            && (flag == 0))
        {
            temp[n][i++] = head[h];
        }
        else if (i != 0)
        {
            flag = 1;
        }
    }

    qsort(temp, n, sizeof(char) * SIZE, cmp);

    for (int m = 0; m < n; m++)
    {   
        if (judge_overlap(temp, temp[m], m))
            continue; 
        
        if (isdefaultword(temp[m]))
            continue;

        printf("%s ", temp[m]);
    }

    return 0;
}

int cmp(const void *a, const void *b)
{
    char *first = (char *) a;
    char *second = (char *) b;

    if (strcmp(first, second) < 0)
        return -1;
    else if (strcmp(first, second) > 0)
        return 1;
    else
        return 0;
}

int judge_overlap(char src[][SIZE], char *obj, int m)
{
    // not the pure digit
    // int j = 0; int flag = 1;
    for (int i = 0; i < m; i++)
    {
        if (!strcmp(src[i], obj))
            return 1;
        // while (src[i][j] != '\0')
        // {
        //     if (!isdigit(src[i][j]))
        //         flag = 0;
        // }
        // if (flag == 1)
        //     break;
        // flag = 1;
        
    }
    return 0;
}

int isdefaultword(char *token)
{
    int num = 0;
    for (num = 0; keywords[num] != NULL; num++)
    {
        if (strcmp(keywords[num], token) == 0)
            return 1;
    }
    return 0;
}

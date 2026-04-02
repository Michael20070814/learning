#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX 200
#define SIZE 2000
#define LENGTH 40

const char *keywords[] = 
{
    "int", "if", "else", "for", "while", "do", "return",
    "main", "void", "char", "float", "double", "switch", 
    "case", "break", "continue", "default", "fopen", NULL
};

bool isdefaultword(char *token);
int retrievedefinedvariable(char result[][LENGTH], FILE *fp);
int searchexistingvariable(FILE *fp, char result[][LENGTH]);
void printneverexistvariable(char result1[][LENGTH], char result2[][LENGTH], int n1, int n2);

int main(void)
{
    char variable[MAX][LENGTH] = {0};
    char existing_variable[MAX][LENGTH] = {0};

    FILE *fp = fopen("int.c", "r");

    int n1 = retrievedefinedvariable(variable, fp);
    int n2 = searchexistingvariable(fp, existing_variable);
    printneverexistvariable(variable, existing_variable, n1, n2);

    return 0;
}

bool isdefaultword(char *token)
{
    int num = 0;
    for (num = 0; keywords[num] != NULL; num++)
    {
        if (strcmp(keywords[num], token) == 0)
            return true;
    }
    return false;
}

int retrievedefinedvariable(char result[][LENGTH], FILE *fp)
{
    char token[LENGTH] = {0};
    int index = 0;

    fscanf(fp, "%s", token);
    while (strcmp(token, "int") != 0)
        fscanf(fp, "%s", token);

    while (true)
    {
        fscanf(fp, "%s", token);
        int num = strcspn(token, ",;");
        if (token[num] == ',')
            token[num] = '\0';
        else if (token[num] == ';')
        {
            token[num] = '\0';
            strcpy(result[index++], token);
            break;
        }
        strcpy(result[index], token);
        index++;
    }

    return index;
}

int searchexistingvariable(FILE *fp, char result[][LENGTH])
{
    int alpha; char buffer[LENGTH];
    int num = 0; int index = 0;
    while ((alpha = fgetc(fp)) != EOF)
    {
        if (isalpha(alpha))
            buffer[num++] = alpha;

        if ((!isalpha(alpha)) && num > 0)
        {    
            buffer[num] = '\0';
            num = 0;
            if (isdefaultword(buffer))
                continue;
            else
                strcpy(result[index++], buffer);
        }
    }
    return index;
}

void printneverexistvariable(char result1[][LENGTH], char result2[][LENGTH], int n1, int n2)
{
    int index1 = 0; int index2 = 0;
    int flag = 0;

    for (; index1 < n1; index1++)
    {
        for (index2 = 0; index2 < n2; index2++)
            if (strcmp(result1[index1], result2[index2]) == 0)
            {   
                flag = 1;
                break;
            }
        if (flag == 0)
            printf("%s\n", result1[index1]);
        else
            flag = 0;
    }
}
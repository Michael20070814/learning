#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 10000

char *input_document(char *input);
void output_document(char *content, char *output);

int main(void)
{
    char src[] = "fcopy.in";
    char obj[] = "fcopy.out";

    char *buffer = input_document(src);

    output_document(buffer, obj);

    free(buffer);

    return 0;
}

char *input_document(char *input)
{
    FILE *fp = fopen(input, "r");
    char *buffer = (char *) malloc(sizeof(char) * SIZE);
    char *output = (char *) malloc(sizeof(char) * SIZE);
    int index = 0;
    char *p = output;

    size_t bytesRead = fread(buffer, 1, SIZE - 1, fp);
    buffer[bytesRead] = '\0'; 

    while (buffer[index] != '\0')
    {
        if (isspace(buffer[index - 1]) && isspace(buffer[index]))
        {
            index++;
            continue;
        }
        else if (buffer[index] == '\t')
        {
            *p = ' ';

        }
        else
            *p = buffer[index];
        p++;
        index++;
    }

    *p = '\0';
    fclose(fp);
    free(buffer);
    return output;
}

void output_document(char *content, char *output)
{
    FILE *fp = fopen(output, "w");
    char *p = content;

    fputs(p, fp);
}
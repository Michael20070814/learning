#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1024
#define WORD 100

typedef struct paper
{
    int id;
    char author[WORD];
    int time;
    char title[WORD];
    char Proceedings[WORD];
} paper;

void process_space(paper input[], int num);
void upper_name(paper input[], int num);
void add_and(paper input[], int num);
void add_space(paper input[], int num);
int cmp(const void *a, const void *b);

int main(void)
{
    char line[1024];
    paper book[100];
    int index = 0;

    while (fgets(line, MAX, stdin) != NULL) // 完成数据的读取
    {
        int i = 0;
        int name = 0; int title = 0; int proceedings = 0;
        while (line[i] == ' ') i++;
        if (line[i] == '\n') continue;
        while (line[i] != '.') book[index].author[name++] = line[i++]; // 处理名字
        book[index].author[name] = '\0';
        i++;
        while (line[i] == ' ') i++;
        sscanf(&line[i], "%d", &book[index].time);
        while (line[i] != '.') i++;
        i = i + 2; // 跳过空格
        while (line[i] != '.') book[index].title[title++] = line[i++];
        book[index].title[title] = '\0';
        i = i + 2;
        while (line[i] != '.') book[index].Proceedings[proceedings++] = line[i++];
        book[index].Proceedings[proceedings] = '\0';
        index++;
        book[index].id = index + 1;
    }

    process_space(book, index);
    upper_name(book, index);
    add_space(book, index);
    add_and(book, index);
    
    qsort(book, index, sizeof(paper), cmp);

    for (int m = 0; m < index; m++)
    {    
        book[m].id = m + 1;
        printf("[%d] %s. %d. %s. %s.\n", book[m].id, book[m].author, 
            book[m].time, book[m].title, book[m].Proceedings);
    }
}

void process_space(paper input[], int num)
{
    for (int n = 0; n < num; n++)
    {
        // 处理名字
        int forth = 0;
        int back = 0;
        while (input[n].author[back] != '\0')
        {
            if (input[n].author[back] == ' ' && (input[n].author[back + 1] == ',' || 
                isspace(input[n].author[back + 1]) || input[n].author[back + 1] == '\0'))
                back++;
            else
                input[n].author[forth++] = input[n].author[back++];
        }
        input[n].author[forth] = '\0';
    }
}

void upper_name(paper input[], int num)
{
    for (int n = 0; n < num; n++)
    {
        int order = 0;
        if (islower(input[n].author[0]))
            input[n].author[0] -= 32;
        char *temp = strstr(input[n].author, "and");
        while (input[n].author[order] != '\0')
        {
            if (temp == NULL && input[n].author[order] == ' ' && islower(input[n].author[order + 1]))
                input[n].author[order + 1] -= 32;
            if (input[n].author[order] == ' ' && islower(input[n].author[order + 1]) 
                && !(temp == &input[n].author[order + 1] && *(temp + 3) == ' '))
                input[n].author[order + 1] -= 32;
            order++;
        }
    }
}

void add_and(paper input[], int num) // 找到最后一个comma替换成and
{
    char buffer[WORD];
    for (int n = 0; n < num; n++)
    {
        int m = 0; int index = -1;
        while (input[n].author[m] != '\0')
        {   
            if (input[n].author[m] == ',')
                index = m;
            m++;
        }
        int buffer_index = 0; int j = 0;
        while (input[n].author[j] != '\0')
        {
            if (index != -1 && (!strstr(input[n].author, "and")))
            {
                if (j != index)
                    buffer[buffer_index++] = input[n].author[j];
                else
                {
                    buffer[buffer_index++] = ' ';
                    buffer[buffer_index++] = 'a';
                    buffer[buffer_index++] = 'n';
                    buffer[buffer_index++] = 'd';
                }
                j++;
            }
            else
                buffer[buffer_index++] = input[n].author[j++];
        }
        buffer[buffer_index] = '\0';
        strcpy(input[n].author, buffer);
    }
}

void add_space(paper input[], int num)
{
    char buffer[WORD];
    
    for (int n = 0; n < num; n++)
    {
        int buffer_index = 0;
        int m = 0; 
        while (input[n].author[m] != '\0')
        {
            if (input[n].author[m] == ',' && input[n].author[m + 1] != ' ')
            {    
                buffer[buffer_index++] = input[n].author[m];
                buffer[buffer_index++] = ' ';
            }
            else
                buffer[buffer_index++] = input[n].author[m];
            m++;
        }
        buffer[buffer_index] = '\0';
        strcpy(input[n].author, buffer);
    }
}

int cmp(const void *a, const void *b)
{
    paper *first = (paper *) a;
    paper *second = (paper *) b;

    char first_author[WORD]; int n;
    char second_author[WORD]; int m;
    for (n = 0; first->author[n] != '\0' && first->author[n] != ','; n++)
        first_author[n] = first->author[n];
    first_author[n] = '\0';
    for (m = 0; second->author[m] != '\0' && second->author[m] != ','; m++)
        second_author[m] = second->author[m];
    second_author[m] = '\0';

    if (first->time > second->time)
        return -1;
    else if (first->time < second->time)
        return 1;
    else if (strcmp(first_author, second_author) < 0)
        return -1;
    else if (strcmp(first_author, second_author) > 0)
        return 1;
    else
        return first->id - second->id; // 按输入顺序
}
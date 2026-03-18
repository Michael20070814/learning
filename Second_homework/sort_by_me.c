#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
#define NAME_SIZE 21
#define PHONE_SIZE 12

typedef struct People
{
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
} People;

int cmp(const void *a, const void *b);
int main(void)
{
    People phone_list[MAX_SIZE];
    int num; int count = 0;
    int name_count[MAX_SIZE] = {0};

    scanf("%d", &num);

    for (int n = 0; n < num; n++)
    {
        char *name = (char *) malloc(sizeof(char) * NAME_SIZE);
        char *phone = (char *) malloc(sizeof(char) * PHONE_SIZE);
        scanf("%s %s", name, phone);

        int duplicate = 0;
        for (int j = 0; j < count; j++)
        {
            if (strcmp(name, phone_list[j].name) == 0 && strcmp(phone, phone_list[j].phone) == 0)
            {    
                duplicate = 1;
                break;
            }
        }
        if (duplicate == 1)
            continue;

        int found = -1;
        for (int j = 0; j < count; j++)
        {
            if (strcmp(name, phone_list[j].name) == 0)
            {
                found = j;
                break;
            }
        }

        if (found == -1) // 没找到
        {
            strcpy(phone_list[count].name, name);
            strcpy(phone_list[count].phone, phone);// 拷贝内容
            name_count[count] = 1;
        }
        else
        {
            char *new_name = (char *)malloc (sizeof(char) * NAME_SIZE);
            sprintf(new_name, "%s_%d", name, name_count[found]++);
            strcpy(phone_list[count].name, new_name);
            strcpy(phone_list[count].phone, phone);
            free(new_name);
        }
        count++;
        free(name);
        free(phone);   
    }

    qsort(phone_list, count, sizeof(People), cmp);

    for (int i = 0; i < count; i++)
        printf("%s %s\n", phone_list[i].name, phone_list[i].phone);

    return 0;
}

int cmp(const void *a, const void *b)
{
    People *first = (People *)a;
    People *second = (People *)b;

    if (strcmp(first->name, second->name) < 0)
        return -1;
    else if (strcmp(first->name, second->name) > 0)
        return 1;
    else
        return 0;
}
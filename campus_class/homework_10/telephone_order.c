#include <stdio.h>
#include <string.h>
typedef struct Customer
{
    char name[11];
    char phone[11];
}Customer;
int main(void)
{
    int num;
    char ch;
    Customer temp;
    Customer client[50];
    scanf("%d", &num);
    while ((ch = getchar()) != '\n')
            continue;
    for (int n = 0; n < num; n++)
    {
        scanf("%10s", client[n].name);
        while ((ch = getchar()) != ' ')
            continue;
        scanf("%10s", client[n].phone);
        while ((ch = getchar()) != '\n')
            continue;
    }
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num - 1; j++)
        {
            if (strcmp(client[j].name, client[j + 1].name) > 0)
            {    
                temp = client[j];
                client[j] = client[j + 1];
                client[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < num; i++)
    {
        printf("%12s", client[i].name);
        printf("%12s", client[i].phone);
        printf("\n");
    }
}
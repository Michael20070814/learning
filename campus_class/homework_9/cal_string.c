#include <stdio.h>
#include <string.h>
struct Str
{
    char alpha;
    int times;
};
void sequence(struct Str ar[], int length);
void swap(struct Str *a, struct Str *b);
int main(void)
{
    struct Str group[50] = {0};
    char temp[100];
    int i, j = 0;
    int value;
    fgets(temp, 100, stdin);
    int length = strlen(temp);
    for (int num = 0; num < length; num++)
    {    
        value = 1;
        for (i = 0; i < 50; i++)
        {    
            if (group[i].alpha == temp[num])
            {    
                value *= 0;
                break;
            }
        }
        if (value == 0)
            group[i].times += 1;
        else
        {
            group[j].alpha = temp[num];
            group[j].times = 1;
            j++;
        }
    }
    sequence(group, j);
    for (int output = 1; output < j; output++)
    {
        printf("%c-%d ", group[output - 1].alpha, group[output - 1].times);
        if (output % 4 == 0)
            printf("\n");
    }
}
void sequence(struct Str ar[], int length)
{
    for (int num = 0; num < length; num++)
        for (int q = 0; q < length; q++)
            if (q< length - 1 && ar[q].times < ar[q + 1].times)
                swap(&ar[q], &ar[q + 1]);
}
void swap(struct Str *a, struct Str *b)
{
    struct Str temp = *a;
    *a = *b;
    *b = temp;
}
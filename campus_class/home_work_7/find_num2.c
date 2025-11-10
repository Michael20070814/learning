#include <stdio.h>
#define LEN 50
int find_small(int x, int y);
int find_big(int x, int y);
int main(void)
{
    int times, min, max;
    int num_group[LEN];

    scanf("%d", &times);
    for (int num = 0; num < times; num++)
        scanf("%d", &num_group[num]);
    min = max = num_group[0];
    for (int num = 0; num < times; num++)
    {
        min = find_small(min, num_group[num]);
        max = find_big(max, num_group[num]);
    }
    printf("%d %d", max, min);
    
    return 0;
}
int find_small(int x, int y)
{
    return (x < y) ? x : y;
}
int find_big(int x, int y)
{
    return (x > y) ? x : y;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct point
{
    int x;
    int y;
} point;

typedef struct lines
{
    point start;
    point end;
} lines;

lines* input(int num);
int find_longest_lines(lines input[], int index, int num);
int equal(point a, point b);

int main(void)
{
    int num = 0;
    scanf("%d", &num);

    // input the line
    lines *head;
    head = input(num);

    // find the longest line from every starter
    int result[num];
    for (int index = 0; index < num; index++)
        result[index] = find_longest_lines(head, index, num);

    // find the max
    int tag = 0;
    int longest = result[0];
    for (int index = 0; index < num; index++)
        if (longest < result[index])
        {    
            longest = result[index];
            tag = index;
        }

    printf("%d %d %d", longest, head[tag].start.x, head[tag].start.y);

    return 0;
}

lines* input(int num)
{
    lines* arr = (lines*)malloc(num * sizeof(lines));
    if (arr == NULL)
        return NULL;
    
    for (int i = 0; i < num; i++)
    {
        scanf("%d %d %d %d",
              &arr[i].start.x,
              &arr[i].start.y,
              &arr[i].end.x,
              &arr[i].end.y);
    }
    
    return arr;
}

int equal(point a, point b)
{
    return (a.x == b.x && a.y == b.y);
}

int find_longest_lines(lines input[], int index, int num)
{
    for (int i = 0; i < num; i++)
    {
        if (equal(input[i].start, input[index].end))
            return find_longest_lines(input, i, num) + 1;
    }
    return 1;
}
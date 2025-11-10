#include <stdio.h>
int square(int x1, int y1, int x2, int y2);
void eatline(void);
int find_small(int x, int y);
int find_big(int x, int y);
int main(void)
{
    int rectangle1[4];
    int rectangle2[4];
    int x1, y1, x2, y2;

    for (int num = 0; num < 4; num++)
        scanf("%d", &rectangle1[num]);
    for (int num = 0; num < 4; num++)
        scanf("%d", &rectangle2[num]);
    x1 = find_big(rectangle1[0], rectangle2[0]);
    y1 = find_small(rectangle1[1], rectangle2[1]);
    x2 = find_small(rectangle1[2], rectangle2[2]);
    y2 = find_big(rectangle1[3], rectangle2[3]);
    if (rectangle1[3] > rectangle2[1] || rectangle1[1] < rectangle2[3] ||
         rectangle1[2] < rectangle2[0] || rectangle2[2] < rectangle1[0])
        printf("0");
    else
        printf("%d", square(x1, y1, x2, y2));
    return 0;
}
int square(int x1, int y1, int x2, int y2)
{
    int length1, length2;
    if (x1 > x2)
        length1 = x1 - x2;
    else 
        length1 = x2 - x1;
    if (y1 > y2)
        length2 = y1 - y2;
    else 
        length2 = y2 - y1;
    return length1 * length2;
}
int find_small(int x, int y)
{
    return (x < y) ? x : y;
}
int find_big(int x, int y)
{
    return (x > y) ? x : y;
}

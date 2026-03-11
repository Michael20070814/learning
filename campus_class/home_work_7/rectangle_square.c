#include <stdio.h>

/*
 * 读取两个矩形（用左上角与右下角坐标表示），输出它们的相交面积；若不相交则输出 0。
 *
 * 输入格式（每个矩形 4 个整数）：
 *   x_left  y_top  x_right  y_bottom
 *
 * 坐标约定：y_top >= y_bottom。
 */

/* 计算由两点 (x1, y1) 与 (x2, y2) 构成的轴对齐矩形面积（即宽*高）。 */
int square(int x1, int y1, int x2, int y2);
/* 历史遗留：本题未使用；保留声明不影响编译。 */
void eatline(void);
/* 返回两数中较小者。 */
int find_small(int x, int y);
/* 返回两数中较大者。 */
int find_big(int x, int y);

int main(void)
{
    /* rectangle[i] 含义：0=x_left, 1=y_top, 2=x_right, 3=y_bottom */
    int rectangle1[4];
    int rectangle2[4];
    int x1, y1, x2, y2;

    /* 读入两个矩形的坐标 */
    for (int num = 0; num < 4; num++)
        scanf("%d", &rectangle1[num]);
    for (int num = 0; num < 4; num++)
        scanf("%d", &rectangle2[num]);

    /* 计算相交矩形的边界：
     *   左边界取两者左边界的较大值
     *   右边界取两者右边界的较小值
     *   上边界取两者上边界的较小值（更“低”的上边界）
     *   下边界取两者下边界的较大值（更“高”的下边界）
     */
    x1 = find_big(rectangle1[0], rectangle2[0]);
    y1 = find_small(rectangle1[1], rectangle2[1]);
    x2 = find_small(rectangle1[2], rectangle2[2]);
    y2 = find_big(rectangle1[3], rectangle2[3]);

    /* 不相交的判定（上下或左右完全分离） */
    if (rectangle1[3] > rectangle2[1] || rectangle1[1] < rectangle2[3] ||
        rectangle1[2] < rectangle2[0] || rectangle2[2] < rectangle1[0])
        printf("0");
    else
        /* 相交则输出相交区域面积 */
        printf("%d", square(x1, y1, x2, y2));

    return 0;
}

int square(int x1, int y1, int x2, int y2)
{
    int length1, length2;

    /* 用差值绝对值作为宽和高，避免坐标大小关系带来的负数 */
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
    /* 三目运算符返回较小值 */
    return (x < y) ? x : y;
}

int find_big(int x, int y)
{
    /* 三目运算符返回较大值 */
    return (x > y) ? x : y;
}

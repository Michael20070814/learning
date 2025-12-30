#include <stdio.h>
int main(void)
{
    int num, k;
    scanf("%d", &num);
    int energy[num];
    int temp[num];
    for (int n = 0; n < num; n++)
        temp[n] = 0;
    for (int n = 0; n < num; n++)
        scanf("%d", &energy[n]);
    scanf("%d", &k);
    if (k > 0)
        for (int n = 0; n < num; n++)
            for (int i = 1; i < k + 1; i++)
                temp[n] += energy[(n + i) % num];
    if (k < 0)
        for (int n = 0; n < num; n++)
            for (int i = -1; i > k - 1; i--)
            {
                if (n + i < 0)
                    temp[n] += energy[num + ((n + i) % num)];
                else
                    temp[n] += energy[(n + i) % num];
            }
    for (int n = 0; n < num; n++)
        printf("%d ", temp[n]);
    
    return 0;
}
/* 
(n * (1 + abs(k)/n) + current - i) % n    21~24行可以这样替换 前面先计算需要多少个n来保证i是正数
也可以使用链表 双向循环链表
*/
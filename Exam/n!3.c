#include <stdio.h>
#include <string.h>

void print(int *v, int n)
{
    for (int i = 0; i < n; i++) printf("%4d", v[i]);
    printf("\n");
}

int nextPermutation(int *v, int n)
{
    // 1. 从右找第一个下降点 i（v[i] < v[i+1]）
    int i = n - 2;
    while (i >= 0 && v[i] >= v[i+1])
        i--;
    if (i < 0) 
        return 0;  // 已是最大排列

    
    int j = n - 1;
    while (v[j] <= v[i]) 
        j--;

    // 3. 交换i和j
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;

    // 4. 翻转i+1之后的部分
    int left = i + 1, right = n - 1;
    while (left < right)
    {
        tmp = v[left];
        v[left] = v[right];
        v[right] = tmp;
        left++; right--;
    }
    return 1;
}

int main() {
    int v[] = {1, 2, 3};
    int n = 3;
    do 
    {
        print(v, n);
    } while (nextPermutation(v, n));
}
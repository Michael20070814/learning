#include <stdio.h>
#define LEN 300
int find_most(int arr[], int size);
int main(void)
{
    char s[LEN];
    int distance[10000];
    int index, j = 0;
    scanf("%s", s); //读入字符串
    for (int n = 0; s[n] != '\0'; n++)
        for (int i = n + 1;s[n] != '\0' && s[i] != '\0'; i++)
            if (s[i] == s[n])
            {    
                distance[j] = i - n - 1; // 前后遍历，寻找相同元素，记录距离
                j++;
            }
    if (j == 0)
        printf("%d", j - 1);
    else
    {
        index = find_most(distance, j);
        printf("%d", index);
    }
    return 0;
}
int find_most(int arr[], int size) // 找出数组中最大元素
{
    int temp;
    temp = arr[0];
    for (int n = 1; n < size; n++)
        if (arr[n] > temp)
            temp = arr[n];
    return temp;
}
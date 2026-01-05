#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100
int main(void)
{
    int length1, length2;
    int alpha1[26] = {0};
    int alpha2[26] = {0};
    char input1[MAX_LENGTH];
    char input2[MAX_LENGTH];
    scanf("%s", input1);
    scanf("%s", input2);
    length1 = strlen(input1);
    length2 = strlen(input2);
    if (length1 != length2)
    {    
        printf("0");
        return 0;
    }
    for (int num = 0; num < length1; num++)
    {
        alpha1[input1[num] - 'a'] += 1;
        alpha2[input2[num] - 'a'] += 1;
    }
    if (!memcmp(alpha1, alpha2, 26 * sizeof(int))) // 应该比较的是alpha所占有的内存大小
        printf("1");
    else
        printf("0");
    
    return 0;
}
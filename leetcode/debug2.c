#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char* addStrings(char* num1, char* num2) 
{
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    int max_len = (length1 > length2) ? length1 : length2;
    char *result = malloc((max_len + 2) * sizeof(char));
    memset(result, '0', (max_len + 2) * sizeof(char));
    for (int num = 0; num < length1; num++)
        result[max_len - num] += num1[length1 - 1 - num] - '0';
    for (int num = 0; num < length2; num++)
        result[max_len - num] += num2[length2 - 1 - num] - '0';
    for (int num = max_len; num >= 0; num--)
    {
        if (result[num] > '9')
        {
            result[num - 1] += 1;
            result[num] = result[num] - 9; 
        }
    }
    result[max_len + 1] = '\0';
    if (result[0] == '0')
        return result + 1;
    else
        return result;
}
int main(void)
{
    char num1[] = "456";
    char num2[] = "77";
    addStrings(num1, num2);
}
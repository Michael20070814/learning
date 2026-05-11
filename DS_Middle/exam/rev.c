#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 500

int type(char ch);
void reverse(char *ar, char *end);

int main(void)
{
    char buffer[500] = {0};

    // 确认读取成功
    if (fgets(buffer, MAXSIZE - 1, stdin) == NULL)
        return 0;

    char *left = buffer;
    char *right = buffer;
    int flag_right = 0;
    flag_right = type(*right);

    while (flag_right == type(*right))
        right++;
    flag_right = type(*right);

    while (*right != '\0')
    {
        reverse(left, right - 1);

        while (*right != '\0' && ((type(*right) != 1) && (type(*right) != 2)))
        {
            right++;
        }
        flag_right = type(*right);


        while (left != right)
            left++;
        
        while (flag_right == type(*right))   
            right++;

        flag_right = type(*right);
        
    }

    
    printf("%s", buffer);


    return 0;
}


void reverse(char *ar, char *end)
{
    char result[MAXSIZE] = {0};
    int index = 0;

    while (ar != end + 1)
    {
        result[index++] = *ar;
        ar++;
    }
    ar--;

    for (int m = 0; m < index; m++)
    {
        *ar = result[m];
        ar--;
    }
}

int type(char ch)
{
    if (isalpha(ch))
        return 1;
    else if (isdigit(ch))
        return 2;
    else
        return -1;
}
#include <stdio.h>
#define LEN 40
char *mystrncpy(char *s1, char *s2, int n)
{
    int count = 0;
    while (count < n && *(s2 + count) != '\0')
    {
        *(s1 + count ) = * (s2 + count);
        count++;
    }
    if (count < n)
        for (; count < n; count++)
            *(s1 + count) = '\0';
    return s1;
}
char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;

    ret_val = fgets(st, n, stdin);
    if (ret_val) //ret_val != NULL
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
int main(void)
{
    char len1[LEN];
    char len2[LEN];
    int num;

    printf("Please enter strings: ");
    while (s_gets(len1, LEN) != NULL)
    {
        printf("Enter the number to copy: ");
        while (scanf("%d", &num) != 1 || num > LEN)//每次只会读取数字，剩下的部分留在缓冲区，要清空
        {
            printf("Please enter another num: ");
            while (getchar() != '\n')
                continue;
        }
        puts(len1);
        mystrncpy(len2, len1, num);
        puts(len2);//可能往后随机读取
        printf("PLease enter another string(Enter EOF to quit)");
    }
    return 0;
}

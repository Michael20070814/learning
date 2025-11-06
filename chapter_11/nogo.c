#include <stdio.h>
#define ANSWER "Grant"
#define SIZE 40
char * s_gets(char * st, int n);

int main(void)
{
    char try[SIZE];

    puts("Who is buried in Grant's tomb?");
    s_gets(try, SIZE);
    while (try != ANSWER)//比较的是两个字符串的地址是否相等而非内容
    {
        puts("No, that's wrong. Try angain.");
        s_gets(try, SIZE);
    }
    puts("That's right.");

    return 0;
}
char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;

    ret_val = fgets(st, n, stdin);//读取到字符串内，只读取n个
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;//找到换行符和字符末尾
        if (st[i] == '\n')//替换换行符
            st[i] = '\0';
        else 
            while (getchar() != '\n')//清空缓存区
                continue;
    }
    return ret_val;
}
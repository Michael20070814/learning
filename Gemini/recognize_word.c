#include <stdio.h>
#include <ctype.h>
int recognize_words(char input[]);
int main(void)
{
    char buffer[200];
    fgets(buffer, 100, stdin);
    int result = recognize_words(buffer);
    printf("%d", result);

    return 0;
}
int recognize_words(char input[])
{
    char *p = input;
    int num = 0;
    while (*p != '\0')
    {
        char *temp = p + 1;
        if (!(isspace(*temp)) && isspace(*p)) // 识别方法依赖于最后读入的换行符
            num++;
        p++;
    } // 没有办法处理前导空格
    return num;
}
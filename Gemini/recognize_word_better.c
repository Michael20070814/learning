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
    int num = 0;
    int in_word = 0; // 状态标志：0表示在空格里，1表示在单词里
    char *p = input;

    while (*p != '\0')
    {
        if (isspace(*p)) 
        {
            // 遇到空格，说明当前不在单词里了（或者还在连续空格里）
            in_word = 0; 
        }
        else 
        {
            // 遇到非空格（字符）
            if (in_word == 0) 
            {
                // 刚才还是0，现在突然遇到字符 -> 说明是新单词的开始！
                num++;      // 计数加1
                in_word = 1; // 标记状态：我现在进入单词内部了
            }
            // 如果 in_word 已经是 1，说明还在同一个单词里，不做操作
        }
        p++;
    }
    return num;
}
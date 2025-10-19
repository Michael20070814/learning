#include <stdio.h>
int main(void)
{
    char ch;
    scanf("%c", &ch);
    for (ch = '$'; ch != 'g'; scanf("%c", &ch))
        printf("%c", ch); //for循环第一个不会改变，先循环再变化
    return 0;
}

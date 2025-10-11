#include <stdio.h>
int main(void)
{
    int number, number3, number5;
    float number2 , number4;
    char ch[40];
    char ch2[40];
    ;
    scanf("%d", &number);
    printf("%d\n", number);
    scanf("%f %E", &number2, &number4);
    printf("%.2f %.2E\n", number2, number4);
    scanf("%s", ch);
    printf("%s\n", ch);
    scanf("%s%d", &ch2, &number5);
    printf("%s %d\n", ch2, number5);
    scanf("%*s%d", &number3);
    printf("%d\n", number3);
    return 0;
}
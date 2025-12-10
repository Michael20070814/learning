#include <stdio.h>
int main(void)
{
    int num1, num2;
    char operator;
    scanf("%d%c%d", &num1, &operator, &num2);
    switch (operator)
    {
        case '+':
        printf("%d", num1 + num2);
        break;
        case '-':
        printf("%d", num1 - num2);
        break;
        case '*':
        printf("%d", num1 * num2);
        break;
        case '/':
        printf("%.2f", ((float)num1) / num2);//要检测一下num2不为0
        break;
        default:
        printf("Errors!");
    }
    
    return 0;
}
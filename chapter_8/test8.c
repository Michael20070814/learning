#include <stdio.h>
void add();
void subtract();
void multiply();
void divide();
void request_enter(float *num1, float *num2);
int main(void)
{
    char ch;

    do
    {
        printf("Enter the operation of your choice: \n");
        printf("a. add\t\ts. subtract\nm.multiply\t\td.divide\nq.quit\n");
        switch(ch = getchar())
        {
            case 'a':
            add();
            break;
            case 's':
            subtract();
            break;
            case 'm':
            multiply();
            break;
            case 'd':
            divide();
            break;
            case 'q':
            break;
            default:
            printf("Please enter the correct option: \n");
        }
        while (getchar() != '\n')
            continue;
    } while (ch != 'q');
    printf("Done!");
    return 0;
}
void add()
{
    float num1, num2;
    request_enter(&num1, &num2);
    printf("%.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
}
void subtract()
{
    float num1, num2;
    request_enter(&num1, &num2);
    printf("%.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
}
void multiply()
{
    float num1, num2;
    request_enter(&num1, &num2);
    printf("%.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
}
void divide()
{
    float num1, num2;
    request_enter(&num1, &num2);
    if (num2 == 0)
    {
        printf("Enter a number other than 0:");
        scanf("%f", &num2);
    }
    printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
}
void request_enter(float *num1, float *num2)
{
    printf("Please enter the first number: ");
    while ((scanf("%f", num1)) !=1)
    {
        printf(" is not a number.\n");
        printf("Please enter a number, such as 2.5, -1.78E8, or 3: ");
    }
    printf("Please enter the second number: ");
    while ((scanf("%f", num2)) !=1)
    {
        printf(" is not a number.\n");
        printf("Please enter a number, such as 2.5, -1.78E8, or 3: ");
    }
}
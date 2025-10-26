#include <stdio.h>//猜测数字,二分法快速猜测
int main(void)
{
    int guess;
    char response;
    char upper_limit = 100;
    char lower_limit = 1;
    guess = (lower_limit + upper_limit) / 2;

    printf("Pick an integer from 1 to 100. I will try to guess ");
    printf("it. \nRespond with a y if my guess is right and with ");
    printf("\na b if it is bigger, or a s if is smaller.\n");
    printf("Uh...is your number %d?\n", (lower_limit + upper_limit) / 2);
    while ((response = getchar()) != 'y')
    {
        if (response == 'b')
        {
            upper_limit = guess;
            printf("Well, then, is it %d?\n", guess = (lower_limit + upper_limit) / 2);
        }
        else if (response == 's')
        {
            lower_limit = guess;
            printf("Well, then, is it %d?\n", guess = (lower_limit + upper_limit) / 2);
        }
        else
            printf("Sorry, I could understand only n or y");
        while (getchar() != '\n')
            continue;//跳过剩余行的输入
    }
    printf("I knew I could do it!\n");

    return 0;
}
#include <stdio.h>
int main(void)
{
    int age;
    float assets;
    char pet[30];/* 字符数组用于储存字符串 */

    printf("Enter your age, assets, and favorite pet.\n");
    scanf("%d %f", &age, &assets);
    scanf("%s", pet);//字符数组不需要&
    printf("%d $%.2f %s\n", age, assets, pet);
    return 0;
}
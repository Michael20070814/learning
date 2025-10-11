#include <stdio.h>
int main(void)
{
    float height;
    char name[20];
    printf("Please enter your height and name: \n");
    scanf("%f %s", &height, name);
    printf("%s, you are %.2f feet tall. \n", name, height);
    return 0;
}
#include <stdio.h>
int main(void)
{
    int score;
    scanf("%d", &score);
    if (score < 0 || score > 100)
        printf("The score is wrong.");
    if (score > 89 && score <= 100)
        printf("A");
    if (score > 79 && score <= 89)
        printf("B");
    if (score > 69 && score <= 79)
        printf("C");
    if (score > 59 && score <= 69)
        printf("D");
    if (score <=59 && score >= 0)
        printf("E");

    return 0;
}
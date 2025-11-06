#include <stdio.h>
int main(void)
{
    int score;
    scanf("%d", &score);
    if (score > 89 && score <= 100)
        printf("A");
    else if (score > 79 && score <= 89)
        printf("B");
    else if (score > 69 && score <= 79)
        printf("C");
    else if (score > 59 && score <= 69)
        printf("D");
    else if (score <=59 && score >= 0)
        printf("E");
    else 
        printf("The score is wrong.");

    return 0;
}
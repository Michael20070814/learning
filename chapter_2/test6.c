#include <stdio.h>
int toes;
int double_toes;
int squared_toes;

int main()
{
    toes = 10;
    double_toes = toes * 2;
    squared_toes = toes * toes;

    printf("toes = %d\n", toes);
    printf("double_toes = %d\n", double_toes);
    printf("squared_toes = %d\n", squared_toes);

    return 0;
}

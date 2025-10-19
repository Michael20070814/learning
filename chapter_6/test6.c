#include <stdio.h>
int square (int n);
int cube (int m);
int main(void)
{
    int up_limit, down_limit, row;
    printf("Please enter a up_limit and a down_limit: ");
    scanf("%d %d", &up_limit, &down_limit);
    printf("integer\tsquare\tcube\n");
    for (row = 0; row <= up_limit - down_limit; row++)
    {
        printf("%d\t%d\t%d", down_limit + row, square(down_limit + row),
                cube(down_limit + row));
        printf("\n");
    }
}
int square(int n)
{
    return n * n;
}
int cube(int m)
{
    return m * m * m;
}
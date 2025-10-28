#include <stdio.h>
void chline(char ch, int i, int j);
int main(void)
{
    char ch;
    ch = getchar();
    chline(ch, 6, 8);
}
void chline(char ch, int i, int j)
{
    for (int count = 1; count <= j; count++)
    {
        for (int count1 = 1; count1 <= i; count1++)
            putchar(ch);
        printf("\n");
    }

}
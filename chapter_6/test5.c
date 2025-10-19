#include <stdio.h>
int main(void)
{
    int row, space;
    char input, letter_up, letter_down;
    printf("Please enter a letter: ");
    scanf("%c", &input);
    for (row = 1; row <= input - 'A' + 1; row++)
    {
        for (space = 1; space <= input - 'A' - row + 1; space++)
            printf(" ");
        for (letter_up = 'A'; letter_up <= 'A' + row - 1; letter_up++)
            printf("%c", letter_up);
        for (letter_down = 'A' + row - 2; letter_down >= 'A'; letter_down--)
            printf("%c", letter_down);
        printf("\n");
    }
    return 0;        
}
#include <stdio.h>
int main()
{
    int asc;
    printf("Enter an ASCII code (0 to 127): ");
    scanf("%d", &asc); 
    printf("The character for ASCII code %d is '%c'\n", asc, asc);
    return 0;
}
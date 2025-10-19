#include <stdio.h>
int main(void)
{
    char letter[26];
    char n;
    int index;
    for (n = 'a', index = 0; index <= 25; n++, index++)
        letter[index]= n;
    for (index = 0; index <= 25; index++)
        printf("%c\n", letter[index]);
    return 0;        
}
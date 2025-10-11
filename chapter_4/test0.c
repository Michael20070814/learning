#include <stdio.h>
#define Q "\"His hamlet was funny without being vulgar.\""
int main(void)
{
    printf("%c%c%c\n", 'H', 102, '\41');
    
    printf("%s\nhas %d characters.\n", Q, sizeof(Q) - 1);//sizeof 后面多一个\0 也可使用strlen
    
    return 0;
}
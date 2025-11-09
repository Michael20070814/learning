#include <stdio.h>
int main(void)
{
    char note[] = "See you at the snack bar.";
    char *ptr;

    ptr = note;
    puts(ptr);
    puts(++ptr);//只调用一次，在起始用的位置之前往后推了一个
    note[7] = '\0';
    puts(note);
    puts(++ptr);
    return 0;
}
#include <stdio.h>
#define DEF "I am a #defined string."
int main(void)
{
    char str1[80] = "An array was initialized to me.";
    const char * str2 = "A pointer was initialized to me.";

    puts("I'm an argument to puts().");
    puts(DEF);
    puts(str1);
    puts(str2);//传入的是地址，可以用指针和数组表示法改变地址
    puts(&str1[5]);
    puts(str2 + 4);
    
    return 0;
}
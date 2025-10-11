#include <stdio.h>
#define PAGES 336
#define WORDS 65618
int main(void)
{
    short num = PAGES;
    short mnum = -PAGES;
    printf("num as short and unsigned short: %hd %hu\n", num, num);
    printf("mnum as short and unsigned short: %hd %hu\n", mnum, mnum);//hu仅有正数，65536-336=65200
    printf("num as int and char: %d %c\n", num, num);
    printf("WORDS as int, short, and char: %d, %hd, %c.\n", WORDS, WORDS, WORDS);//大于256，则以256为模
    //65618>65536,65618-65536=82以65536为模
    return 0;
}
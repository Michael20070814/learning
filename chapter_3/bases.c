#include <stdio.h>
int main(void)
{
    int x = 100;

    printf("dec = %d; octal = %o; hex = %x\n", x, x, x);/* octal 八进制 hex 十六进制 */
    printf("dec = %d; octal = %#o; hex = %#x\n", x, x, x);/* # 代表在八进制前加0，在十六进制前加0x */
    return 0;
}
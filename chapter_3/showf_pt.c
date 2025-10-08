#include <stdio.h>
int main(void)
{
    float aboat = 32000.0;
    double abet = 2.14e9;
    long double dip = 5.32e-5;

    printf("%f can be written %e\n",aboat,aboat);// %f 表示浮点数的转换说明， %e 表示指数形式的转换说明
    printf("And it's %a in hexadecimal, powers of 2 notation\n", aboat);/* 0x前缀表示十六进制， p是指e， 2的幂代替10的幂 */
    printf("%f can be written %e\n", abet, abet);
    printf("%Lf can be written %Le\n", dip, dip);// long double 使用 %Lf 和 %Le 和 %La

    return 0;
}
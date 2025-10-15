#include <stdio.h>
int main(void)
{
    int sec_oper;
    int fir_oper;
    printf("This program computes moduli.\n");
    printf("Enter an integer to serve as the second operand:");
    scanf("%d", &sec_oper);
    printf("Now enter the first operand:");
    scanf("%d", &fir_oper);
    while (fir_oper > 0)
    {
        printf("%d %% %d is %d.\n", fir_oper, sec_oper, fir_oper % sec_oper);
        printf("Enter next number for first operand:(<= 0 to quit)");
        scanf("%d", &fir_oper);
    }
    printf("Done!\n");
    return 0;
}
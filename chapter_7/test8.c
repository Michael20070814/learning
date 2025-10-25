#include <stdio.h>//选项选择工资数字，计算税率
#define OVER_WORKING_RATIO 1.5
#define TAX_INFORNT 0.15
#define TAX_MIDDLE 0.2
#define TAX_BACK 0.25
int main(void)
{
    float working_hours, tax_pay, total_wage, wage;
    char wage_level;
    do
    {
        printf("*****************************************************************\n");
        printf("Enter the number corresponding to the desired pay rate or action:\n");
        printf("1) $8.75/hr\t\t\t\t\t2)$9.33/hr\n");
        printf("3) $10.00/hr\t\t\t\t\t4)$11.20/hr\n");
        printf("5) quit\n");
        printf("*****************************************************************\n");
        scanf("%c", &wage_level);
        switch(wage_level)
        {
            case '1':
            wage = 8.75;
            break;
            case '2':
            wage = 9.33;
            break;
            case '3':
            wage = 10.00;
            break;
            case '4':
            wage = 11.20;
            break;
            case '5':
            break;
            default:
            printf("Please enter the correct option again: \n");
        }
    } while (wage_level < '1' || wage_level > '5');
    if (wage_level != '5')
    {
        printf("Please enter your working hours per week: ");
        scanf("%f", &working_hours);
        total_wage = working_hours * wage;
        if (total_wage <= 300)
            tax_pay = TAX_INFORNT * total_wage;
        else if (total_wage <= 450)
            tax_pay = TAX_INFORNT * 300 + (total_wage - 300) * TAX_MIDDLE;
        else
            tax_pay = TAX_INFORNT * 300 + TAX_MIDDLE * 150 + (total_wage - 450) * TAX_BACK;
        printf("Your total wage is %.2f, and the tax is %.2f, the income is %.2f\n", total_wage, tax_pay, total_wage - tax_pay);
    }
    printf("Done!\n");
    return 0;
}
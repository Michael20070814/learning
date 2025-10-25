#include <stdio.h>
#define WAGE 10.0
#define OVER_WORKING_RATIO 1.5
#define TAX_INFORNT 0.15
#define TAX_MIDDLE 0.2
#define TAX_BACK 0.25
int main(void)
{
    float working_hours, tax_pay, total_wage;
    printf("Please enter your working hours per week: ");
    scanf("%f", &working_hours);
    total_wage = working_hours * WAGE;
    if (total_wage <= 300)
        tax_pay = TAX_INFORNT * total_wage;
    else if (total_wage <= 450)
        tax_pay = TAX_INFORNT * 300 + (total_wage - 300) * TAX_MIDDLE;
    else
        tax_pay = TAX_INFORNT * 300 + TAX_MIDDLE * 150 + (total_wage - 450) * TAX_BACK;
    printf("Your total wage is %.2f, and the tax is %.2f, the income is %.2f", total_wage, tax_pay, total_wage - tax_pay);
    return 0;
}
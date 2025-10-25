#include <stdio.h>
#include <stdbool.h>
#define ARTICHOKE_PRICE 2.05
#define BEET_PRICE 1.15
#define CARROT_PRICE 1.09
#define DISCOUNT 0.95
int main(void)
{
    char ch;
    float artichoke_weight, beet_weight, carrot_weight;
    float temp, total_price, total_weight, transport_fee, total_fee;
    bool isDiscount = 0;

    printf("**************************************\n");
    printf("What you want to buy?\n");
    printf("a)artichoke\t\t\tb)beet\n");
    printf("c)carrot\t\t\td)quit\n");
    printf("**************************************\n");

    do
    {
        switch (ch = getchar())
        {
            case 'a':
            printf("Please enter the kilograms of the artichoke: \n");
            while (scanf("%f", &temp) == 1)
                artichoke_weight += temp;
            break;
            case 'b':
            printf("Please enter the kilograms of the beet: \n");
            while (scanf("%f", &temp) == 1)
                beet_weight += temp;
            break;
            case 'c':
            printf("Please enter the kilograms of the carrot: \n");
            while (scanf("%f", &temp) == 1)
                carrot_weight += temp;
            break;
            default:
            break;
        }
    }while (ch != 'd');

    total_price = artichoke_weight * ARTICHOKE_PRICE + beet_weight * BEET_PRICE + 
                carrot_weight * CARROT_PRICE;
    total_weight = carrot_weight + artichoke_weight + beet_weight;
    if (total_price >= 100)
    {
        total_price *= DISCOUNT;
        isDiscount = 1;
    }
    if (total_weight <= 5)
        transport_fee = 6.5;
    else if (total_weight <= 20)
        transport_fee = 14;
    else
        transport_fee = 14 + (total_weight - 20) * 0.5;
    total_fee = total_price + transport_fee;
    
    printf("category\tprice\t\tweight\t\tfee\t\n");
    printf("artichoke\t2.05$/kg\t%.2fkg\t\t%.2f$\n", artichoke_weight, artichoke_weight * ARTICHOKE_PRICE);
    printf("beet\t\t1.15$/kg\t%.2fkg\t\t%.2f$\n", beet_weight, beet_weight * BEET_PRICE);
    printf("carrot\t\t1.09$/kg\t%.2fkg\t\t%.2f$\n", carrot_weight, carrot_weight * CARROT_PRICE);
    if (isDiscount)
    printf("Discount: 95%%\n");
    printf("Transportation fee is %.2f$\n", transport_fee);
    printf("Total fee is %.2f$\n", total_fee);
    return 0;
}
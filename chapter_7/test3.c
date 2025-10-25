#include <stdio.h>
#define MAX_NUM 50
int main(void)

{
    int size, input, num1, num2, odd_sum, even_sum;
    int odd[MAX_NUM];
    int even[MAX_NUM];
    num1 = num2 = odd_sum = even_sum = 0;
    printf("Please enter the number of integer you want to enter: (max for 100)\n");
    scanf("%d", &size);
    printf("Please enter an integer:(enter 0 to quit)");
    scanf("%d", &input);
    while (input != 0)
    {
        if (input % 2 == 0)
        {
            even[num1] = input;
            num1 += 1;
        }
        else 
        {
            odd[num2] = input;
            num2 += 1;
        }
        printf("Please enter another integer: ");
        scanf("%d", &input);
    }
    for (int i = 0; i < num1; i++)
    {
        even_sum += even[i]; 
    }
    for (int j = 0; j < num2; j++)
    {
        odd_sum += odd[j]; 
    }
    printf("You enter %d even integer in total. The average for them is %.2f\n", 
            num1, (float)even_sum / num1);
    printf("You enter %d odd integer in total. The average for them is %.2f\n", 
            num2, (float)odd_sum / num2);
    return 0;
}
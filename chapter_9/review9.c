#include <stdio.h>
void menu(void);
int response(int low, int high);
int main(void)
{
    int result;
    menu();
    result = response(0, 5);
    printf("%d. You are right!\n", result);
    return 0;
}
void menu(void)
{
    printf("Please choose one of the following: \n");
    printf("1) copy files\t\t2) move files\n");
    printf("3) remove files\t\t4)quit\n");
    printf("Enter the number of your choice: \n");
    return;
}
int response(int low, int high)
{
    int input;
    if (scanf("%d", &input) != 1)
        return 4;
    while (input < low || input > high)
    {
        menu();
        scanf("%d", &input);
    }
    return input;
}
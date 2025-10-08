#include <stdio.h>
int main(void)
{
    int cup;
    printf("Enter your cup number:");
    scanf("%d", &cup);
    printf("Your capacity in pint is %.1f.\n", cup / 2.0);
    printf("Your capacity in ounce is %.1f.\n", cup * 8.0);
    printf("Your capacity in tablespoon is %.1f.\n", cup * 16.0); /* tablespoon表示大汤勺  */
    printf("Your capacity in teaspoon is %.1f.\n", cup * 48.0);
    return 0;
}
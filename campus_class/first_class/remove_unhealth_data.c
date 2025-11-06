#include <stdio.h>
int main(void)
{
    int hr[10] = {0, 75, 300, 56, 90, 70, 76, 99, 63 ,16};
    if (hr[0] < 40 || hr[0] > 200)
        hr[0] = 80;
    for (int count = 0; count < 10; count++)
    {
        if (hr[count] < 40 || hr[count] > 200)
            hr[count] = hr[count - 1];
    }
    for (int count = 0; count < 10; count++)
        printf("%d ", hr[count]);

    return 0;
}
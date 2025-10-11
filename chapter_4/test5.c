#include <stdio.h>
int main(void)
{
    float rate;
    float size;
    printf("Please enter your download rate and the document size: (Mb/s and MB)");
    scanf("%f %f", &rate, &size);
    printf("At %.2f megabits per second, a file of %.2f megabytes \ndownloads in %.2f seconds.", rate, size, size*8/rate);
    return 0;  

}
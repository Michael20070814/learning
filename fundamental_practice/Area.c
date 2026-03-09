#include <stdio.h>
#define SIZE 4

int intersect_area(int A[SIZE], int B[SIZE]);
void input(int A[SIZE], int B[SIZE]);

int main(void)
{
    int A[SIZE], B[SIZE];

    input(A, B);

    int Square_area = intersect_area(A, B);

    printf("%d", Square_area);

    return 0;
}

int intersect_area(int A[SIZE], int B[SIZE])
{
    int MAX_AX = (A[0] > A[1]) ? A[0] : A[1];
    int MIN_AX = (A[0] < A[1]) ? A[0] : A[1];
    int MAX_BX = (A[2] > A[3]) ? A[2] : A[3];
    int MIN_BX = (A[2] < A[3]) ? A[2] : A[3];
    int sect_x = ((MAX_AX > MAX_BX) ? MAX_BX : MAX_AX) - ((MIN_AX > MIN_BX) ? MIN_AX : MIN_BX);

    int MAX_AY = (B[0] > B[1]) ? B[0] : B[1];
    int MIN_AY = (B[0] < B[1]) ? B[0] : B[1];
    int MAX_BY = (B[2] > B[3]) ? B[2] : B[3];
    int MIN_BY = (B[2] < B[3]) ? B[2] : B[3];
    int sect_y = ((MAX_AY > MAX_BY) ? MAX_BY : MAX_AY) - ((MIN_AY > MIN_BY) ? MIN_AY : MIN_BY);

    if (sect_x > 0 && sect_y > 0)
        return sect_x * sect_y;
    else
        return 0;
}

void input(int A[SIZE], int B[SIZE])
{
    scanf("%d %d %d %d", &A[0], &B[0], &A[1], &B[1]);
    scanf("%d %d %d %d", &A[2], &B[2], &A[3], &B[3]);
}
#include <stdio.h>
int main(void)
{
    int zippo[4][2] = {{ 2 , 4}, { 6, 8}, { 1, 3 }, {5, 7}};
    int (*pz)[2];
    pz = zippo;// 指向一整个二维数组 需要进行两次解引用 不过起初只设定为下面那一次的元素个数或类型

    printf("  pz = %p,     pz + 1 = %p\n",   pz, pz + 1);
    printf("pz[0] = %p. pz[0] + 1 = %p\n",  pz[0], pz[0] + 1);
    printf("  *pz = %p,   *pz + 1 = %p\n",  *pz, *pz + 1);
    printf(" *pz[0] = %d\n", **pz);
    printf("   **pz = %d\n", **pz);
    printf("     pz[2][1] = %d\n", pz[2][1]);
    printf("*(*(pz + 2)+1 ) = %d", *(*(pz + 2)+ 1));

    return 0;
}
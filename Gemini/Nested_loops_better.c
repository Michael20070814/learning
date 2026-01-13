#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100 // 假设题目最大范围是 100

int main(void)
{
    int row, col;
    int arr[MAX_N][MAX_N]; // 使用固定大小，避免兼容性问题
    int flag = 0; // 是否找到鞍点的标志

    if (scanf("%d%d", &row, &col) != 2) return 0;

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            scanf("%d", &arr[i][j]);

    // --- 核心逻辑开始 ---
    for (int i = 0; i < row; i++) // 遍历每一行
    {
        // 1. 先找出这一行的最大值是多少
        int max_val = arr[i][0];
        for (int j = 1; j < col; j++) {
            if (arr[i][j] > max_val) max_val = arr[i][j];
        }

        // 2. 遍历这一行所有列，只要等于最大值，就去检查它是不是列最小
        //    (这样就解决了“行中有多个相同最大值”的问题)
        for (int j = 0; j < col; j++) 
        {
            if (arr[i][j] == max_val) // 它是行最大之一
            {
                // 3. 检查它是不是列最小
                bool is_col_min = true;
                for (int k = 0; k < row; k++) {
                    if (arr[k][j] < max_val) { // 如果这一列有个元素比它还小
                        is_col_min = false;
                        break;
                    }
                }

                if (is_col_min) {
                    printf("%d at (%d, %d)\n", max_val, i, j);
                    flag = 1;
                }
            }
        }
    }
    // --- 核心逻辑结束 ---

    if (flag == 0)
        printf("No Saddle Point");

    return 0;
}
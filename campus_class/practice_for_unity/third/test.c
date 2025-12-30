#include "src\unity.h"  
#include <stdio.h>
void setUp(void)// 测试开始前运行
{

}

void tearDown(void)// 测试用例结束后运行
{

}

float func_c(float temp, int mode) {
    if (mode == 1) {
        return (temp * 9 / 5) + 32;
    } else if (mode == 2) {
        return (temp - 32) * 5 / 9;
    }
    return -999.0f;
}

void test(void)
{
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 122.0f, func_c(50, 1));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, func_c(50, 2));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -999.0f, func_c(50, 3));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}
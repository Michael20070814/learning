#include <stdio.h>
#include "src\unity.h"
int func_a(int a, int b) 
{
    if (a > b) {
        return a - b;
    } else if (a < b) {
        return b - a;
    }
    return 0;
}

void setUp(void)// 测试开始前运行
{

}

void tearDown(void)// 测试用例结束后运行
{

}

void test_Example(void)// 测试用例
{
    int a = 9;
    int b = 4;
    TEST_ASSERT_EQUAL(5, func_a(9, 4));
    TEST_ASSERT_EQUAL(5, func_a(4, 9));
    TEST_ASSERT_EQUAL(0, func_a(4, 4));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_Example);
    return UNITY_END();
}
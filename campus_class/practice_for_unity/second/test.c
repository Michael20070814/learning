#include "src\unity.h"  
#include <stdio.h>
void setUp(void)// 测试开始前运行
{

}

void tearDown(void)// 测试用例结束后运行
{

}

int func_b(int year) { // 每一个if都是两个分支
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 100 == 0) {
        return 0;
    }
    if (year % 4 == 0) {
        return 1;
    }
    return 0;
}

void test(void)
{
    TEST_ASSERT_TRUE(func_b(400));
    TEST_ASSERT_FALSE(func_b(100));
    TEST_ASSERT_TRUE(func_b(16));
    TEST_ASSERT_FALSE(func_b(19));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}
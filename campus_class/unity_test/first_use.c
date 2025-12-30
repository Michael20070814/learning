#include "src/unity.h"
#include <stdio.h>
#define CALC_ERROR -1

void setUp(void)// 测试开始前运行
{

}

void tearDown(void)// 测试用例结束后运行
{

}

void test_Example(void)// 测试用例
{
    int result = 1 + 1;
    TEST_ASSERT_EQUAL(2, result); // 断言
}

int main(void)
{
    UNITY_BEGIN(); // 初始化测试引擎
    RUN_TEST(test_Example); // 运行测试函数
    return UNITY_END(); // 结束并输出结果
}
#include "../unity/src/unity.h"
#include "../src/src.h"
#include <stdio.h>

void setUp(void)// 测试开始前运行
{

}

void tearDown(void)// 测试用例结束后运行
{

}

void test1(void)// 测试用例
{
    TEST_ASSERT_EQUAL(1, detect1101("1101")); // 断言
}
void test2(void)// 测试用例
{
    TEST_ASSERT_EQUAL(2, detect1101("1101101")); // 断言
}
void test3(void)// 测试用例
{
    TEST_ASSERT_EQUAL(2, detect1101("11011101")); // 断言
}
void test4(void)// 测试用例
{
    TEST_ASSERT_EQUAL(0, detect1101("")); // 断言
}
void test5(void)// 测试用例
{
    TEST_ASSERT_EQUAL(0, detect1101("10")); // 断言
}
void test6(void)// 测试用例
{
    TEST_ASSERT_EQUAL(0, detect1101("1111111111")); // 断言
}
void test7(void)// 测试用例
{
    TEST_ASSERT_EQUAL(0, detect1101("0000000000")); // 断言
}
void test8(void)
{
    TEST_ASSERT_EQUAL(0, detect1101("1100")); // 断言
}

int main(void)
{
    UNITY_BEGIN(); // 初始化测试引擎
    RUN_TEST(test1); // 运行测试函数
    RUN_TEST(test2); 
    RUN_TEST(test3); 
    RUN_TEST(test4); 
    RUN_TEST(test5); 
    RUN_TEST(test6); 
    RUN_TEST(test7);
    RUN_TEST(test8);
    return UNITY_END(); // 结束并输出结果
}
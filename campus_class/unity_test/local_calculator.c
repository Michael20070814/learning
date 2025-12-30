#include "src/unity.h"
#include <stdio.h>
#include <ctype.h>
#define CALC_ERROR -1

void setUp(void)// 测试开始前运行
{

}

void tearDown(void)// 测试用例结束后运行
{

}

float calculator(int a, int b, char op)// 测试函数
{
    if (!isNatural(a) || !isNatural(b)){
    printf("Error: Negative input\n");
    return CALC_ERROR;
    }
    float result = 0.0;
    switch(op){
    case '+':
    result = a + b; break;
    case '-':
    result = a - b; break;
    case '*':
    result = a * b; break;
    case '/':
    if(b != 0){
    result = (float)a / b;
    }else{
    printf("Error: Division by zero\n");
    return CALC_ERROR;
    }
    break;
    default:
    printf("Error: Unknown operator '%c'\n", op);
    return CALC_ERROR;
    }
    return roundf(result * 100) / 100.0f;
}
void test_calculator(void)
{
    float a = 1.0;
    int b = 5;
    int c = 9;
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 14.00f, calculator(b, c, '+'));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 4.00f, calculator(c, b, '-'));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.56f, calculator(b, c, '/'));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 45.00f, calculator(b, c, '*'));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, calculator(b, 0, '/'));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, calculator(b, c, '='));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, calculator(c, -b, '+'));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, calculator(-c, b, '+'));
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_calculator);

    return UNITY_END();
}
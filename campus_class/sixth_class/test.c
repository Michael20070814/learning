#include "../unity/src/unity.h"
#include <stdlib.h>
#include "../src/src.h"

void setUp(void) {
    // Optional setup before each test case
}

void tearDown(void) {
    // Optional cleanup after each test case
}

void test_your_func(void) {
    // add tests
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
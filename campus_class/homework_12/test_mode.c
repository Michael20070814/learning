#include <stdio.h>
#include <stdlib.h>

#include "../unity/src/unity.h"
#include "../src/src.h"

void setUp(void) {
    // Optional setup before each test case
}

void tearDown(void) {
    // Optional cleanup after each test case
}

void test_func1(void){
    TEST_ASSERT_EQUAL(calc_system_state(0), 0);
}
void test_func2(void){
    TEST_ASSERT_EQUAL(calc_system_state(1), 10);
}
void test_func3(void){
    TEST_ASSERT_EQUAL(calc_system_state(2), 20);
}
void test_func4(void){
    TEST_ASSERT_EQUAL(calc_system_state(3), 30);
}
void test_func5(void){
    TEST_ASSERT_EQUAL(calc_system_state(6), 40);
}
void test_func6(void){
    TEST_ASSERT_EQUAL(calc_system_state(8), -100);
}
void test_func7(void){
    TEST_ASSERT_EQUAL(calc_system_state(4), -1);
}
void test_func8(void){
    TEST_ASSERT_EQUAL(calc_system_state(5), -1);
}
void test_func9(void){
    TEST_ASSERT_EQUAL(calc_system_state(7), -1);
}
void test_func10(void){
    TEST_ASSERT_EQUAL(calc_system_state(16), -1);
}
void test_func11(void){
    TEST_ASSERT_EQUAL(calc_system_state(12), -100);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_func1);
    RUN_TEST(test_func2);
    RUN_TEST(test_func3);
    RUN_TEST(test_func4);
    RUN_TEST(test_func5);
    RUN_TEST(test_func6);
    RUN_TEST(test_func7);
    RUN_TEST(test_func8);
    RUN_TEST(test_func9);
    RUN_TEST(test_func10);
    RUN_TEST(test_func11);

    return UNITY_END();
}
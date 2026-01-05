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
    TEST_ASSERT_EQUAL(calc_fee(-1), -1);
}
void test_func2(void){
    TEST_ASSERT_EQUAL(calc_fee(0), 10);
}
void test_func3(void){
    TEST_ASSERT_EQUAL(calc_fee(35), 20);
}
void test_func4(void){
    TEST_ASSERT_EQUAL(calc_fee(75), 35);
}
void test_func5(void){
    TEST_ASSERT_EQUAL(calc_fee(125), 50);
}
void test_func6(void){
    TEST_ASSERT_EQUAL(calc_fee(30), 10);
}
void test_func7(void){
    TEST_ASSERT_EQUAL(calc_fee(60), 20);
}
void test_func8(void){
    TEST_ASSERT_EQUAL(calc_fee(120), 35);
}
void test_func9(void){
    TEST_ASSERT_EQUAL(calc_fee(110), 35);
}
void test_func10(void){
    TEST_ASSERT_EQUAL(calc_fee(10), 10);
}
void test_func11(void){
    TEST_ASSERT_EQUAL(calc_fee(31), 20);
}
void test_func12(void){
    TEST_ASSERT_EQUAL(calc_fee(61), 35);
}
void test_func13(void){
    TEST_ASSERT_EQUAL(calc_fee(180), 50);
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
    RUN_TEST(test_func12);
    RUN_TEST(test_func13);

    return UNITY_END();
}
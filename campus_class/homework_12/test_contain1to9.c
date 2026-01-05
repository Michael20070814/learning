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
    int num[] = {1, 3, 4};
    TEST_ASSERT_EQUAL(-2, contain1to9(num, 3));
}
void test_func2(void){
    int num[] = {1, 3, 4, 5, 9, 10, 11, 12, 19, 2, 7, 8};
    TEST_ASSERT_EQUAL(-2, contain1to9(num, 12));
}
void test_func3(void){
    int num[] = {1, 3, 4, 5, 9, 10, 11, 12, 19};
    TEST_ASSERT_EQUAL(-1, contain1to9(num, 9));
}
void test_func4(void){
    int num[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    TEST_ASSERT_EQUAL(1, contain1to9(num, 9));
}
void test_func5(void){
    int num[] = {11, 12, 13, 14, 15, 16, 17, 18, 19};
    TEST_ASSERT_EQUAL(-1, contain1to9(num, 9));
}
void test_func6(void){
    int num[] = {};
    TEST_ASSERT_EQUAL(-2, contain1to9(num, 0));
}
void test_func7(void){
    int num[] = {1, 2, 3, 4, 5, 6, 7, 8, 8};
    TEST_ASSERT_EQUAL(0, contain1to9(num, 9));
}
void test_func8(void){
    int num[] = {0, 2, 3, 4, 5, 6, 7, 8, 8};
    TEST_ASSERT_EQUAL(-1, contain1to9(num, 9));
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


    return UNITY_END();
}
#include "../unity/src/unity.h"
#include "../src/src.h"

void setUp(void) {
    // Optional setup before each test case
}

void tearDown(void) {
    // Optional cleanup after each test case
}

void test_func1(void){
    TEST_ASSERT_EQUAL(-1, determine_triangle_type(-1, 2, 3));
}
void test_func2(void){
    TEST_ASSERT_EQUAL(1, determine_triangle_type(3, 3, 3));
}
void test_func3(void){
    TEST_ASSERT_EQUAL(2, determine_triangle_type(3, 3, 4));
}
void test_func4(void){
    TEST_ASSERT_EQUAL(3, determine_triangle_type(3, 5, 4));
}
void test_func5(void){
    TEST_ASSERT_EQUAL(0, determine_triangle_type(3, 3, 8));
}
void test_func6(void){
    TEST_ASSERT_EQUAL(2, determine_triangle_type(4, 3, 3));
}
void test_func7(void){
    TEST_ASSERT_EQUAL(2, determine_triangle_type(3, 4, 3));
}
void test_func8(void){
    TEST_ASSERT_EQUAL(0, determine_triangle_type(8, 3, 3));
}
void test_func9(void){
    TEST_ASSERT_EQUAL(0, determine_triangle_type(3, 8, 3));
}
void test_func10(void){
    TEST_ASSERT_EQUAL(3, determine_triangle_type(3, 4, 5));
}
void test_func11(void){
    TEST_ASSERT_EQUAL(3, determine_triangle_type(5, 4, 3));
}
void test_func12(void){
    TEST_ASSERT_EQUAL(3, determine_triangle_type(5, 3, 4));
}
void test_func13(void){
    TEST_ASSERT_EQUAL(3, determine_triangle_type(4, 3, 5));
}
void test_func14(void){
    TEST_ASSERT_EQUAL(3, determine_triangle_type(4, 5, 3));
}
void test_func15(void){
    TEST_ASSERT_EQUAL(-1, determine_triangle_type(1001, 2, 3));
}
void test_func16(void){
    TEST_ASSERT_EQUAL(0, determine_triangle_type(0, 2, 3));
}
void test_func17(void){
    TEST_ASSERT_EQUAL(2, determine_triangle_type(3, 4, 4));
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
    RUN_TEST(test_func14);
    RUN_TEST(test_func15);
    RUN_TEST(test_func16);
    RUN_TEST(test_func17);

    return UNITY_END();
}
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
    struct UserSummary user1 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    struct UserSummary user2 = 
    {
        .userID = 3,
        .totalAmount = 980.2,
        .count = 6
    };
    TEST_ASSERT_LESS_OR_EQUAL(0, compareSummary(&user1, &user2));
}
void test_func2(void){
    struct UserSummary user1 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    struct UserSummary user2 = 
    {
        .userID = 3,
        .totalAmount = 999.2,
        .count = 6
    };
    TEST_ASSERT_GREATER_OR_EQUAL(0, compareSummary(&user1, &user2));
}
void test_func3(void){
    struct UserSummary user1 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    struct UserSummary user2 = 
    {
        .userID = 3,
        .totalAmount = 987.2,
        .count = 6
    };
    TEST_ASSERT_GREATER_OR_EQUAL(0, compareSummary(&user1, &user2));
}
void test_func4(void){
    struct UserSummary user1 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    struct UserSummary user2 = 
    {
        .userID = 3,
        .totalAmount = 987.2,
        .count = 4
    };
    TEST_ASSERT_LESS_OR_EQUAL(0, compareSummary(&user1, &user2));
}
void test_func5(void){
    struct UserSummary user1 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    struct UserSummary user2 = 
    {
        .userID = 3,
        .totalAmount = 987.2,
        .count = 5
    };
    TEST_ASSERT_GREATER_OR_EQUAL(0, compareSummary(&user1, &user2));
}
void test_func6(void){
    struct UserSummary user1 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    struct UserSummary user2 = 
    {
        .userID = 1,
        .totalAmount = 987.2,
        .count = 5
    };
    TEST_ASSERT_LESS_OR_EQUAL(0, compareSummary(&user1, &user2));
}
void test_func7(void){
    struct UserSummary user1 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    struct UserSummary user2 = 
    {
        .userID = 2,
        .totalAmount = 987.2,
        .count = 5
    };
    TEST_ASSERT_LESS_OR_EQUAL(0, compareSummary(&user1, &user2));
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

    return UNITY_END();
}
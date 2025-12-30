void test_calculator(void) 
{
float result = result = calculator(10, 5, '+');
TEST_ASSERT_FLOAT_WITHIN(0.001f, 15.00f, result);
result = calculator(10, 5, '-');
TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.00f, result);
result = calculator(10, 5,
'*');
TEST_ASSERT_FLOAT_WITHIN(0.001f, 50.00f, result);
result = calculator(10, 5, '/');
TEST_ASSERT_FLOAT_WITHIN(0.001f, 2.00f, result);
result = calculator(10, 0, '/');
TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, result); // Expecting CALC_ERROR
result = calculator(10, 5, '%');
TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, result); // Expecting CALC_ERROR
result = calculator(10, -5, '+');
TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, result); // Expecting CALC_ERROR
result = calculator(-10, 5, '+');
TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0, result); // Expecting CALC_ERROR
}
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_calculator);

    return UNITY_END();
}
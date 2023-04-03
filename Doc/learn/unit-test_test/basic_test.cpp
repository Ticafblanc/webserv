#include <gtest/gtest.h>
#include "basic.cpp"

TEST(basic_test, calculatorTest){
    EXPECT_EQ(calculator(2, 2), 2);
    EXPECT_EQ(calculator(2, 5), 7);
}

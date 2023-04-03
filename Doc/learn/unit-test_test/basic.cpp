#include <gtest/gtest.h>

int calculator(int x, int y)
{
	return (x + y);
}

TEST(basic, calculator)
{
	EXPECT_EQ(calculator(2,2), 4);
	EXPECT_EQ(calculator(2,2), 4);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
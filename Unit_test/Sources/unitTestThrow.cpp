#include "../Include/unit_test.hpp"
#include <stdexcept>

int	throw_test()
{
	throw std::range_error("test");
	return 10;
}

TEST
{
	int (*func)();
	func = &throw_test;
	TEST_THROW(func, std::invalid_argument);
	std::cout << "test" << std::endl;
}

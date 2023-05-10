#include "../Include/unit_test.hpp"
#include <stdexcept>

int	unitTestThrow()
{
	throw (std::out_of_range("test"));
}

int main () {
	
	EXPECT_THROW(unitTestThrow(), std::out_of_range);
	return 0;
}

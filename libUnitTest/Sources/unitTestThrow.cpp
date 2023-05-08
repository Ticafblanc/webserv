#include "../Include/unit_test.hpp"
#include <stdexcept>

int	unitTestThrow()
{
	throw (std::invalid_argument("test"));
}

int main () {
	
	EXPECT_THROW(unitTestThrow(), std::out_of_range);
	return 0;
}

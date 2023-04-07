#include "../Include/unit_test.hpp"

int unitTestLauncher()
{
	try {
		std::vector<server> server_vec = init("../../usr->local/etc/webserv/webserv.conf");
		std::vector<server>::iterator server_it = server_vec.begin();
		for(; server_it != server_vec.end(); server_it++)
			server_it->launcher();
	}
	catch (const std::exception & e) {
		e.what();
		return (TEST_FAIL);
	}
	return (TEST_PASS);
}

TEST
{
	TEST_EQ(unitTestLauncher(), TEST_PASS);
	return (TEST_PASS);
}

#include "JsonValueSuite.hpp"

int main(void)
{
	std::cout << "Preparing test suite" << std::endl;
	JsonValueSuite *suite = new JsonValueSuite();
	suite->run();
	suite->report();
}

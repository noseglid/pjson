#include "JsonValueSuite.hpp"

int main(void)
{
	JsonValueSuite *suite = new JsonValueSuite();
	suite->run();
	suite->report();
	delete suite;
}

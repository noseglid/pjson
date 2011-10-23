#include "JsonValueSuite.hpp"

#include <iostream>

int main(void)
{
	try {
		JsonValueSuite *suite = new JsonValueSuite();
		suite->run();
		suite->report();
		delete suite;
	} catch (Json::Exception e) {
		std::cout << "Uncaught JSON exception: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "Uncaught unknown exception. You know what you did!" << std::endl;
	}
}

#include "JsonValueSuite.hpp"
#include "JsonBuilderSuite.hpp"

#include <iostream>

int main(void)
{
	try {
		JsonValueSuite *valuesuite = new JsonValueSuite();
		valuesuite->run();
		valuesuite->report();
		delete valuesuite;

		JsonBuilderSuite *buildersuite = new JsonBuilderSuite();
		buildersuite->run();
		buildersuite->report();
		delete buildersuite;

	} catch (Json::Exception e) {
		std::cout << "Uncaught JSON exception: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "Uncaught unknown exception. You know what you did!" << std::endl;
	}
}

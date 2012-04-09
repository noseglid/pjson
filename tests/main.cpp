#include "JsonValueSuite.hpp"
#include "JsonBuilderSuite.hpp"
#include "JsonStringSuite.hpp"
#include "PjsonSuite.hpp"

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

		JsonStringSuite *stringsuite = new JsonStringSuite();
		stringsuite->run();
		stringsuite->report();
		delete stringsuite;

		PjsonSuite *pjsonsuite = new PjsonSuite();
		pjsonsuite->run();
		pjsonsuite->report();
		delete pjsonsuite;

	} catch (Json::Exception e) {
		std::cout << "Uncaught JSON exception: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "Uncaught unknown exception. You know what you did!" << std::endl;
	}
}

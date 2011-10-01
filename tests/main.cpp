#include "PJsonValueSuite.hpp"

#include <cpptest.h>

int main(void)
{
	PJsonValueSuite suite;
	Test::TextOutput output(Test::TextOutput::Verbose);
	return suite.run(output) ? EXIT_SUCCESS : EXIT_FAILURE;
}

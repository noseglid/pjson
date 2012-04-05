#ifndef __PJSONSUITE_HPP__
#define __PJSONSUITE_HPP__

#include <pjson/pjson.hpp>
#include <vector>
#include <string>
#include <iostream>

class PjsonSuite
{
	public:
		PjsonSuite() {};

		void run();
		void report();

	private:
		void testSerialize();
		void testDeserialize();
};

#endif

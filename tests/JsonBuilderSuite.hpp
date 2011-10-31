#ifndef __JSONBUILDERSUITE_HPP__
#define __JSONBUILDERSUITE_HPP__

#include <pjson/pjson.hpp>
#include <vector>
#include <string>
#include <iostream>

class JsonBuilderSuite
{
	public:
		JsonBuilderSuite() {};

		void run();
		void report();

	private:
		void teststring();
		void testnumber();
		void testbool();
		void testnull();
		void testobject();
		void testarray();
		void testmixed();

		void testMultipleArray();
		void testMultipleObject();
		void testMultipleMixed();
};

#endif

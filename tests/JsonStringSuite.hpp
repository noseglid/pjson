#ifndef __JSONSTRINGSUITE_HPP__
#define __JSONSTRINGSUITE_HPP__

#include <pjson/pjson.hpp>
#include <vector>
#include <string>
#include <iostream>

class JsonStringSuite
{
	public:
		JsonStringSuite() {};

		void run();
		void report();

	private:
		void stringstring();
		void stringnull();
		void stringbool();
		void stringnumber();
		void stringobject();
		void stringarray();
};

#endif

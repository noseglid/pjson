#ifndef __JSONVALUESUITE_HPP__
#define __JSONVALUESUITE_HPP__

#include <pjson/pjson.hpp>
#include <vector>
#include <string>
#include <iostream>

class JsonValueSuite
{
	public:
		JsonValueSuite() {};

		void run();
		void report();

	private:
		void copyConstructor();
		void assignment();

		void validString();
		void invalidString();
		void validNumber();
		void invalidNumber();
		void validObject();
		void invalidObject();
		void validBool();
		void invalidBool();
		void validNull();
		void invalidNull();
		void validArray();
		void invalidArray();
		void validNested();
		void invalidNested();
		void getType();
		void getOperator();
		void invalidGetOperator();

		void invalidGet();
};

#endif

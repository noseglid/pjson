#ifndef __JSONVALUESUITE_H__
#define __JSONVALUESUITE_H__

#include <pjson/pjson.hpp>
#include <vector>
#include <string>
#include <iostream>

class JsonValueSuite
{
	public:
		JsonValueSuite()
		{
			std::cout << "Running suite 'JsonValue'." << std::endl;
		};

		void run();
		void report();

	private:
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
		void getType();
		void getOperator();
		void invalidGetOperator();
		void validNested();
};

#endif

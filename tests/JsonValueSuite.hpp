#ifndef _TESTJSONVALUESUITE_H_
#define _TESTJSONVALUESUITE_H_

#include <pjson/pjson.hpp>
#include <vector>
#include <string>

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
};

#endif

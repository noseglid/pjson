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
		};

		void run();
		void report();

	private:
		std::vector<std::string> failed;

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

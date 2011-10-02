#ifndef _TESTJSONVALUESUITE_H_
#define _TESTJSONVALUESUITE_H_

#include <pjson.hpp>
#include <cpptest.h>

class JsonValueSuite: public Test::Suite
{
	public:
		JsonValueSuite()
		{
			TEST_ADD(JsonValueSuite::validString)
			TEST_ADD(JsonValueSuite::invalidString)
			TEST_ADD(JsonValueSuite::validNumber)
			TEST_ADD(JsonValueSuite::invalidNumber)
			TEST_ADD(JsonValueSuite::validObject)
			TEST_ADD(JsonValueSuite::invalidObject)
			TEST_ADD(JsonValueSuite::validBool)
			TEST_ADD(JsonValueSuite::invalidBool)
			TEST_ADD(JsonValueSuite::validNull)
			TEST_ADD(JsonValueSuite::invalidNull)
			TEST_ADD(JsonValueSuite::validArray)
			TEST_ADD(JsonValueSuite::invalidArray)
			TEST_ADD(JsonValueSuite::getType)
		};

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

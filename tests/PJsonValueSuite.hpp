#ifndef _TESTPJSONVALUESUITE_H_
#define _TESTPJSONVALUESUITE_H_

#include <pjson.hpp>
#include <cpptest.h>

class PJsonValueSuite: public Test::Suite
{
	public:
		PJsonValueSuite()
		{
			TEST_ADD(PJsonValueSuite::validString)
			TEST_ADD(PJsonValueSuite::invalidString)
			TEST_ADD(PJsonValueSuite::validNumber)
			TEST_ADD(PJsonValueSuite::invalidNumber)
			TEST_ADD(PJsonValueSuite::validObject)
			TEST_ADD(PJsonValueSuite::invalidObject)
			TEST_ADD(PJsonValueSuite::validBool)
			TEST_ADD(PJsonValueSuite::invalidBool)
			TEST_ADD(PJsonValueSuite::validNull)
			TEST_ADD(PJsonValueSuite::invalidNull)
			TEST_ADD(PJsonValueSuite::validArray)
			TEST_ADD(PJsonValueSuite::invalidArray)
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
};

#endif

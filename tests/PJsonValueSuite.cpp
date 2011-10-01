#include "PJsonValueSuite.hpp"

#include <cpptest.h>
#include <pjson.hpp>

#include <fstream>
#include <sstream>

using namespace std;

static string
readfile(const char *file)
{
	ifstream is;
	is.open(file, ios::binary);

	if (!is.good()) {
		cout << "Could not open file: " << file << endl;
		return string();
	}

	// get length of file:
	is.seekg(0, ios::end);
	int length = is.tellg();
	is.seekg(0, ios::beg);

	// allocate memory:
	char buffer[length];

	// read data as a block:
	is.read(buffer, length);
	is.close();
	string ret = string(buffer, length);

	return ret;
}

void
PJsonValueSuite::validString()
{
	try {
		string json1 = readfile("data/validstring1.json");
		PJsonValue p1(json1);
		TEST_ASSERT("My single value string" == p1.asString());

		string json2 = readfile("data/validstring2.json");
		PJsonValue p2(json2);
		TEST_ASSERT("This is a valid \"json\" string" == p2.asString());
	} catch (exception e) {
		cout << e.what() << endl;
		TEST_ASSERT(false);
	}
}

void
PJsonValueSuite::invalidString()
{
	try {
		string json1 = readfile("data/invalidstring1.json");
		TEST_THROWS(PJsonValue p1(json1), PJsonException);

		string json2 = readfile("data/invalidstring2.json");
		TEST_THROWS(PJsonValue p2(json2), PJsonException);
	} catch (exception e) {
		cout << e.what() << endl;
		TEST_ASSERT(false);
	}
}

void
PJsonValueSuite::validNumber()
{
	try {
		string json1 = readfile("data/validnumber1.json");
		PJsonValue p1(json1);
		TEST_ASSERT(int(5) == p1.asInt());

		string json2 = readfile("data/validnumber2.json");
		PJsonValue p2(json2);
		TEST_ASSERT_DELTA(float(85.5), p2.asFloat(), 0.0001);

		string json3 = readfile("data/validnumber3.json");
		PJsonValue p3(json3);
		TEST_ASSERT_DELTA(float(-0.0674), p3.asFloat(), 0.0001);
	} catch (exception e) {
		cout << e.what() << endl;
		TEST_ASSERT(false);
	}
}

void
PJsonValueSuite::invalidNumber()
{
	try {
		string json1 = readfile("data/invalidnumber1.json");
		TEST_THROWS(PJsonValue p1(json1), PJsonException);

		string json2 = readfile("data/invalidnumber2.json");
		TEST_THROWS(PJsonValue p2(json2), PJsonException);
	} catch (exception e) {
		cout << e.what() << endl;
		TEST_ASSERT(false);
	}
}

void
PJsonValueSuite::validObject()
{
	try {
		string j1 = readfile("data/validobject1.json");
		PJsonValue p1(j1);
		TEST_ASSERT(p1.asMap()["key1"]->asString() == "val1");

		string j2 = readfile("data/validobject2.json");
		PJsonValue p2(j2);
		TEST_ASSERT(p2.asMap()["key with \"quotes\""]->asString() ==
		                       "value 2 with ws and \"quotes\"");

		string j3 = readfile("data/validobject3.json");
		PJsonValue p3(j3);
		TEST_ASSERT(p3.asMap()["key1"]->asString() == "val1");
		TEST_ASSERT(p3.asMap()["key2"]->asString() == "val2");
		TEST_ASSERT(p3.asMap()["key3"]->asString() == "val3");

		string j4 = readfile("data/validobject4.json");
		PJsonValue p4(j4);
		TEST_ASSERT(p4.asMap()["key1"]->asInt()    == 123);
		TEST_ASSERT(p4.asMap()["key2"]->asFloat()  == 12e6);
		TEST_ASSERT(p4.asMap()["key3"]->asBool()   == true);
		TEST_ASSERT(p4.asMap()["key4"]->asBool()   == false);
		TEST_ASSERT(p4.asMap()["key5"]->asString() == "string");
		TEST_ASSERT(p4.asMap()["key6"]->asString() == "false");

		string j5 = readfile("data/validobject5.json");
		PJsonValue p5(j5);

		TEST_ASSERT(p5.asMap()["d1key1"]->asMap()["d2key1"]->asString() == "d2val1");
		TEST_ASSERT(p5.asMap()["d1key1"]->asMap()["d2key2"]->asInt()    == 23);
		TEST_ASSERT(p5.asMap()["d1key2"]->asString() == "d1val2");
		TEST_ASSERT(p5.asMap()["d1key3"]->asFloat()  == 52.4e6);
	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

void
PJsonValueSuite::invalidObject()
{
	try {
		string json1 = readfile("data/invalidobject1.json");
		TEST_THROWS(PJsonValue p(json1), PJsonException);

		string json2 = readfile("data/invalidobject2.json");
		TEST_THROWS(PJsonValue p(json2), PJsonException);
	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

void
PJsonValueSuite::validBool()
{
	try {
		string json1 = readfile("data/validbool1.json");
		PJsonValue p1(json1);
		TEST_ASSERT(p1.asBool() == true);

		string json2 = readfile("data/validbool2.json");
		PJsonValue p2(json2);
		TEST_ASSERT(p2.asBool() == false);

	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

void
PJsonValueSuite::invalidBool()
{
	try {
		string json3 = readfile("data/invalidbool1.json");
		TEST_THROWS(PJsonValue p3(json3), PJsonException);

		string json4 = readfile("data/invalidbool2.json");
		TEST_THROWS(PJsonValue p4(json4), PJsonException);
	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

void
PJsonValueSuite::validNull()
{
	try {
		string json1 = readfile("data/validnull1.json");
		PJsonValue p1(json1);
		TEST_ASSERT(p1.isNull() == true);
	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

void
PJsonValueSuite::invalidNull()
{
	try {
		string json1 = readfile("data/invalidnull1.json");
		TEST_THROWS(PJsonValue p1(json1), PJsonException);
	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

void
PJsonValueSuite::validArray()
{
	try {
		string json1 = readfile("data/validarray1.json");
		PJsonValue p1(json1);
		TEST_ASSERT(p1.asArray()[0]->asString() == "singlevalue");

		string json2 = readfile("data/validarray2.json");
		PJsonValue p2(json2);
		TEST_ASSERT(p2.asArray()[0]->asString() == "multivalue");
		TEST_ASSERT(p2.asArray()[1]->isNull()   == true);
		TEST_ASSERT(p2.asArray()[2]->asFloat()  == 12e9);
		TEST_ASSERT(p2.asArray()[3]->asBool()   == false);
		TEST_ASSERT(p2.asArray()[4]->asMap()["key1"]->asString() == "val1");
		TEST_ASSERT(p2.asArray()[5]->asBool()   == true);
		TEST_ASSERT(p2.asArray()[6]->asInt()    == 22);
	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

void
PJsonValueSuite::invalidArray()
{
	try {
		string json1 = readfile("data/invalidarray1.json");
		TEST_THROWS(PJsonValue p1(json1), PJsonException);

		string json2 = readfile("data/invalidarray2.json");
		TEST_THROWS(PJsonValue p2(json2), PJsonException);

		string json3 = readfile("data/invalidarray3.json");
		TEST_THROWS(PJsonValue p3(json3), PJsonException);
	} catch (PJsonException e) {
		TEST_ASSERT_MSG(false, e.what());
	} catch (exception stde) {
		TEST_ASSERT_MSG(false, "Unexpected exception.");
	}
}

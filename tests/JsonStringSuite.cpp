#include "pjtestframework.hpp"
#include "JsonStringSuite.hpp"

#include <pjson/pjson.hpp>

void
JsonStringSuite::run()
{
	std::cout << "Running suite 'JsonStringSuite'.";

	this->stringstring();
	this->stringnull();
	this->stringbool();
	this->stringnumber();
	this->stringobject();
	this->stringarray();
}

void
JsonStringSuite::report()
{
	std::cout << pjreport();
}

void
JsonStringSuite::stringstring()
{
	Json::Value v1 = Json::Builder::create(std::string("MyJsonString"));
	TEST_ASSERT("\"MyJsonString\"", v1.strjson());

	Json::Value v2 = Json::Builder::create(std::string("[Stuff with \" say \\  \" \"{"));
	TEST_ASSERT("\"[Stuff with \\\" say \\\\  \\\" \\\"{\"", v2.strjson());
}

void
JsonStringSuite::stringnull()
{
	Json::Value v1 = Json::Builder::create();
	TEST_ASSERT("null", v1.strjson());
}

void
JsonStringSuite::stringbool()
{
	Json::Value v1 = Json::Builder::create(true);
	TEST_ASSERT("true", v1.strjson());

	Json::Value v2 = Json::Builder::create(false);
	TEST_ASSERT("false", v2.strjson());
}

void
JsonStringSuite::stringnumber()
{
	Json::Value v1 = Json::Builder::create(42);
	TEST_ASSERT("42", v1.strjson());

	Json::Value v2 = Json::Builder::create(-1238);
	TEST_ASSERT("-1238", v2.strjson());

	Json::Value v3 = Json::Builder::create(42e2);
	TEST_ASSERT("4200", v3.strjson());
}

void
JsonStringSuite::stringobject()
{
	std::map<std::string, int> m1;
	m1["A"] = 123;
	m1["B"] = 42;
	m1["C"] = 27138;

	Json::Value v1 = Json::Builder::create(m1);
	std::string exp1 = readfile("data/strjson/object1.json");
	TEST_ASSERT(exp1, v1.strjson());

	std::map<std::string, std::string> m2;
	m2["1"] = "what";
	m2["2"] = "is";
	m2["3"] = "up, ";
	m2["4"] = "dawg?";

	Json::Value v2 = Json::Builder::create(m2);
	std::string exp2 = readfile("data/strjson/object2.json");
	TEST_ASSERT(exp2, v2.strjson());
}

void
JsonStringSuite::stringarray()
{
	std::vector<std::string> a1;
	a1.push_back("I am good");
	a1.push_back("I am happy");
	a1.push_back("I am extravagant");
	a1.push_back("I am drunk");

	Json::Value v1 = Json::Builder::create(a1);
	std::string exp1 = readfile("data/strjson/array1.json");
	TEST_ASSERT(exp1, v1.strjson());

	std::vector<int> a2;
	a2.push_back(1);
	a2.push_back(1);
	a2.push_back(2);
	a2.push_back(3);
	a2.push_back(5);
	a2.push_back(8);
	a2.push_back(13);
	a2.push_back(21);
	a2.push_back(34);
	a2.push_back(55);
	a2.push_back(89);
	a2.push_back(144);

	Json::Value v2 = Json::Builder::create(a2);
	std::string exp2 = readfile("data/strjson/array2.json");
	TEST_ASSERT(exp2, v2.strjson());
}

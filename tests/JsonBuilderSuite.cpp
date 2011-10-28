#include "pjtestframework.hpp"
#include "JsonBuilderSuite.hpp"

#include <iostream>
#include <limits>
#include <pjson/pjson.hpp>

void
JsonBuilderSuite::run()
{
	std::cout << "Running suite 'JsonBuilder'.";

	this->teststring();
	this->testnumber();
	this->testbool();
	this->testnull();
	this->testobject();
	this->testarray();
	this->testmixed();
}

void
JsonBuilderSuite::report()
{
	std::cout << pjreport();
}

void
JsonBuilderSuite::teststring()
{
	Json::Value v1 = Json::Builder::create(std::string("somevalue"));
	TEST_ASSERT("somevalue", v1.asString());

	Json::Value v2 = Json::Builder::create(std::string("some value \"escaped\" stuff, 123"));
	TEST_ASSERT("some value \"escaped\" stuff, 123", v2.asString());
}

void
JsonBuilderSuite::testnumber()
{
	Json::Value v1 = Json::Builder::create(32);
	TEST_ASSERT(Json::JVNUMBER, v1.getType());
	TEST_ASSERT(32, v1.asInt());

	Json::Value v2 = Json::Builder::create(32.2);
	TEST_ASSERT(Json::JVNUMBER, v2.getType());
	TEST_ASSERT(32.2, v2.asNumber());

	int max = std::numeric_limits<int>::max();
	Json::Value v3 = Json::Builder::create(max);
	TEST_ASSERT(Json::JVNUMBER, v3.getType());
	TEST_ASSERT(max, v3.asInt());

	Json::Value v4 = Json::Builder::create(127e2);
	TEST_ASSERT(Json::JVNUMBER, v4.getType());
	TEST_ASSERT(127e2, v4.asNumber());
}

void
JsonBuilderSuite::testbool()
{
	bool t = true, f = false;
	Json::Value v1 = Json::Builder::create(t);
	TEST_ASSERT(Json::JVBOOL, v1.getType());
	TEST_ASSERT(true, v1.asBool());

	Json::Value v2 = Json::Builder::create(f);
	TEST_ASSERT(Json::JVBOOL, v2.getType());
	TEST_ASSERT(false, v2.asBool());
}

void
JsonBuilderSuite::testnull()
{
	Json::Value v1 = Json::Builder::create();
	TEST_ASSERT(Json::JVNULL, v1.getType());
	TEST_ASSERT(true, v1.isNull());
}

void
JsonBuilderSuite::testobject()
{
	std::map<std::string, std::string> m1;
	m1["life"]  = std::string("The meaning of life is 42");
	m1["death"] = std::string("Is the meaning of death 84?");
	Json::Value v1 = Json::Builder::create(m1);
	TEST_ASSERT("The meaning of life is 42",   v1["life"].asString());
	TEST_ASSERT("Is the meaning of death 84?", v1["death"].asString());

	std::map<std::string, bool> m2;
	m2["is_life_rough"] = true;
	m2["are_you_sad"]   = false;
	Json::Value v2 = Json::Builder::create(m2);
	TEST_ASSERT(true, v2["is_life_rough"].asBool());
	TEST_ASSERT(false, v2["are_you_sad"].asBool());

	std::map<std::string, int> m3;
	m3["meaning_of_life"]    = 42;
	m3["harry_potter_books"] = 7;
	Json::Value v3 = Json::Builder::create(m3);
	TEST_ASSERT(42, v3["meaning_of_life"].asInt());
	TEST_ASSERT(7, v3["harry_potter_books"].asInt());
}

void
JsonBuilderSuite::testarray()
{
	std::vector<int> a1;
	for (int i = 0; i < 10; ++i) a1.push_back(i);
	Json::Value v1 = Json::Builder::create(a1);
	for (int i = 0; i < 10; ++i) TEST_ASSERT(i, v1[i].asInt());

	std::vector<std::string> a2;
	a2.push_back("Some people never learn");
	a2.push_back("or do they?");
	Json::Value v2 = Json::Builder::create(a2);
	TEST_ASSERT("Some people never learn", v2[0].asString());
	TEST_ASSERT("or do they?", v2[1].asString());
}

void
JsonBuilderSuite::testmixed()
{
	std::map<std::string, Json::value_t> m1;
	m1["int"]    = 42;
	m1["string"] = std::string("Where art thou?");
	m1["bool"]   = false;
	m1["double"] = 3.2e-1;

	Json::Value v1 = Json::Builder::create(m1);
	TEST_ASSERT(42, v1["int"].asInt());
	TEST_ASSERT("Where art thou?", v1["string"].asString());
	TEST_ASSERT(false, v1["bool"].asBool());
	TEST_ASSERT(3.2e-1, v1["double"].asNumber());
}

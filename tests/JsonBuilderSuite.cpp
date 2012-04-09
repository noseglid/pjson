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

	this->testMultipleArray();
	this->testMultipleObject();
	this->testMultipleMixed();
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
	TEST_ASSERT(Json::JVSTRING, v1.getType());
	TEST_ASSERT("somevalue", v1.asString());

	Json::Value v2 = Json::Builder::create(std::string("some value \"escaped\" stuff, 123"));
	TEST_ASSERT(Json::JVSTRING, v2.getType());
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
	Json::Value v1 = Json::Builder::create(true);
	TEST_ASSERT(Json::JVBOOL, v1.getType());
	TEST_ASSERT(true, v1.asBool());

	Json::Value v2 = Json::Builder::create(false);
	TEST_ASSERT(Json::JVBOOL, v2.getType());
	TEST_ASSERT(false, v2.asBool());
}

void
JsonBuilderSuite::testnull()
{
	Json::Value v1 = Json::Builder::create(Json::Null());
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
	m1["int"]      = 42;
	m1["string"]   = std::string("Where art thou?");
	m1["bool"]     = false;
	m1["double"]   = 3.2e-1;
	m1["charstar"] = "What is this?";
	m1["null"]     = Json::Null();

	Json::Value v1 = Json::Builder::create(m1);
	TEST_ASSERT(42, v1["int"].asInt());
	TEST_ASSERT("Where art thou?", v1["string"].asString());
	TEST_ASSERT(false, v1["bool"].asBool());
	TEST_ASSERT(3.2e-1, v1["double"].asNumber());
	TEST_ASSERT("What is this?", v1["charstar"].asString());
	TEST_ASSERT(true, v1["null"].isNull());
}

void
JsonBuilderSuite::testMultipleArray()
{
	std::vector<std::vector<int> > top;

	std::vector<int> v1;
	v1.push_back(5);
	v1.push_back(6);
	v1.push_back(42);
	top.push_back(v1);

	std::vector<int> v2;
	v2.push_back(-21);
	v2.push_back(-22);
	v2.push_back(-2183);
	top.push_back(v2);

	Json::Value jv1 = Json::Builder::create(top);
	TEST_ASSERT(5, jv1[0][0].asInt());
	TEST_ASSERT(6, jv1[0][1].asInt());
	TEST_ASSERT(42, jv1[0][2].asInt());
	TEST_ASSERT(-21, jv1[1][0].asInt());
	TEST_ASSERT(-22, jv1[1][1].asInt());
	TEST_ASSERT(-2183, jv1[1][2].asInt());

	/* This is just stupid, but designed to work. Who knows? */
	std::vector<std::vector<std::vector< std::string> > > l3;
	std::vector<std::vector<std::string> > l2;
	std::vector<std::string> l1;
	l1.push_back("first");
	l1.push_back("second");
	l2.push_back(l1);
	l3.push_back(l2);
	Json::Value jv2 = Json::Builder::create(l3);
	Json::Value jv3 = Json::Builder::create(l2);
	Json::Value jv4 = Json::Builder::create(l1);

	TEST_ASSERT("first", jv4[0].asString());
	TEST_ASSERT("second", jv4[1].asString());
	TEST_ASSERT("first", jv3[0][0].asString());
	TEST_ASSERT("second", jv3[0][1].asString());
	TEST_ASSERT("first", jv2[0][0][0].asString());
	TEST_ASSERT("second", jv2[0][0][1].asString());
}

void
JsonBuilderSuite::testMultipleObject()
{
	std::map<std::string, std::map<std::string, int> > top;
	std::map<std::string, int> m1;
	m1["a"] = 0;
	m1["b"] = 1;
	m1["c"] = 2;

	std::map<std::string, int> m2;
	m2["x"] = 911;
	m2["y"] = 112;
	m2["z"] = 323;
	top["struct1"] = m1;
	top["struct2"] = m2;
	Json::Value jv1 = Json::Builder::create(top);
	TEST_ASSERT(0, jv1["struct1"]["a"].asInt());
	TEST_ASSERT(1, jv1["struct1"]["b"].asInt());
	TEST_ASSERT(2, jv1["struct1"]["c"].asInt());
	TEST_ASSERT(911, jv1["struct2"]["x"].asInt());
	TEST_ASSERT(112, jv1["struct2"]["y"].asInt());
	TEST_ASSERT(323, jv1["struct2"]["z"].asInt());
}

void
JsonBuilderSuite::testMultipleMixed()
{
	std::map<std::string, std::vector<int> > m1;
	std::vector<int> m1v1;
	m1v1.push_back(1);
	m1v1.push_back(2);
	std::vector<int> m1v2;
	m1v2.push_back(3);
	m1v2.push_back(4);
	m1["v1"] = m1v1;
	m1["v2"] = m1v2;
	Json::Value jv1 = Json::Builder::create(m1);
	TEST_ASSERT(1, jv1["v1"][0].asInt());
	TEST_ASSERT(2, jv1["v1"][1].asInt());
	TEST_ASSERT(3, jv1["v2"][0].asInt());
	TEST_ASSERT(4, jv1["v2"][1].asInt());

	/* Now this is just ... */
	std::vector<std::map<std::string, std::vector<int> > > v1;
	std::map<std::string, std::vector<int> > v1m1;
	std::map<std::string, std::vector<int> > v1m2;
	std::vector<int> v1m1v1;
	std::vector<int> v1m1v2;
	std::vector<int> v1m2v1;
	std::vector<int> v1m2v2;

	v1m1v1.push_back(0);
	v1m1v1.push_back(1);
	v1m1v2.push_back(2);
	v1m1v2.push_back(3);
	v1m2v1.push_back(4);
	v1m2v1.push_back(5);
	v1m2v2.push_back(6);
	v1m2v2.push_back(7);

	v1m1["v1m1v1"] = v1m1v1;
	v1m1["v1m1v2"] = v1m1v2;
	v1m2["v1m2v1"] = v1m2v1;
	v1m2["v1m2v2"] = v1m2v2;
	v1.push_back(v1m1);
	v1.push_back(v1m2);
	Json::Value jv2 = Json::Builder::create(v1);

	TEST_ASSERT(0, jv2[0]["v1m1v1"][0].asInt());
	TEST_ASSERT(1, jv2[0]["v1m1v1"][1].asInt());
	TEST_ASSERT(2, jv2[0]["v1m1v2"][0].asInt());
	TEST_ASSERT(3, jv2[0]["v1m1v2"][1].asInt());
	TEST_ASSERT(4, jv2[1]["v1m2v1"][0].asInt());
	TEST_ASSERT(5, jv2[1]["v1m2v1"][1].asInt());
	TEST_ASSERT(6, jv2[1]["v1m2v2"][0].asInt());
	TEST_ASSERT(7, jv2[1]["v1m2v2"][1].asInt());
}

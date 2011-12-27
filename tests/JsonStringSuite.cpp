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

	this->deepArray();
	this->deepObject();
	this->mixed();
}

void
JsonStringSuite::report()
{
	std::cout << pjreport();
}

void
JsonStringSuite::stringstring()
{
	std::string ser1 = Json::serialize(std::string("MyJsonString"));
	TEST_ASSERT("\"MyJsonString\"", ser1);

	std::string ser2 = Json::serialize(std::string("[Stuff with \" say \\  \" \"{"));
	TEST_ASSERT("\"[Stuff with \\\" say \\\\  \\\" \\\"{\"", ser2);
}

void
JsonStringSuite::stringnull()
{
	Json::Value v = Json::Builder::create();
	TEST_ASSERT("null", Json::serialize(v));
}

void
JsonStringSuite::stringbool()
{
	std::string ser1 = Json::serialize(true);
	TEST_ASSERT("true", ser1);

	std::string ser2 = Json::serialize(false);
	TEST_ASSERT("false", ser2);
}

void
JsonStringSuite::stringnumber()
{
	std::string ser1 = Json::serialize(42);
	TEST_ASSERT("42", ser1);

	std::string ser2 = Json::serialize(-1238);
	TEST_ASSERT("-1238", ser2);

	std::string ser3 = Json::serialize(42e2);
	TEST_ASSERT("4200", ser3);
}

void
JsonStringSuite::stringobject()
{
	std::map<std::string, int> m1;
	m1["A"] = 123;
	m1["B"] = 42;
	m1["C"] = 27138;

	std::string ser1 = Json::serialize(m1);
	std::string exp1 = readfile("data/strjson/object1.json");
	TEST_ASSERT(exp1, ser1);

	std::map<std::string, std::string> m2;
	m2["1"] = "what";
	m2["2"] = "is";
	m2["3"] = "up, ";
	m2["4"] = "dawg?";

	std::string ser2 = Json::serialize(m2);
	std::string exp2 = readfile("data/strjson/object2.json");
	TEST_ASSERT(exp2, ser2);
}

void
JsonStringSuite::stringarray()
{
	std::vector<std::string> a1;
	a1.push_back("I am good");
	a1.push_back("I am happy");
	a1.push_back("I am extravagant");
	a1.push_back("I am drunk");

	std::string ser1 = Json::serialize(a1);
	std::string exp1 = readfile("data/strjson/array1.json");
	TEST_ASSERT(exp1, ser1);

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

	std::string ser2 = Json::serialize(a2);
	std::string exp2 = readfile("data/strjson/array2.json");
	TEST_ASSERT(exp2, ser2);
}

void
JsonStringSuite::deepArray()
{
	std::vector<std::vector<int> > vct;
	std::vector<int> value;
	value.push_back(1);
	value.push_back(2);
	vct.push_back(value);
	std::string ser1 = Json::serialize(vct);
	std::string exp1 = readfile("data/strjson/array3.json");
	TEST_ASSERT(exp1, ser1);

	std::vector<std::vector<std::vector<int > > > l1;
	std::vector<std::vector<int> > l2_1, l2_2, l2_3;
	std::vector<int> l3_1, l3_2, l3_3;
	l3_1.push_back(1);
	l3_1.push_back(1);
	l3_1.push_back(2);
	l3_1.push_back(3);
	l3_1.push_back(5);

	l3_2.push_back(2);
	l3_2.push_back(3);
	l3_2.push_back(5);
	l3_2.push_back(7);
	l3_2.push_back(11);

	l3_3.push_back(1);
	l3_3.push_back(2);
	l3_3.push_back(6);
	l3_3.push_back(24);
	l3_3.push_back(120);

	l2_1.push_back(l3_1);
	l2_1.push_back(l3_2);
	l2_1.push_back(l3_3);

	l2_2.push_back(l3_1);
	l2_2.push_back(l3_2);
	l2_2.push_back(l3_3);

	l2_3.push_back(l3_1);
	l2_3.push_back(l3_2);
	l2_3.push_back(l3_3);

	l1.push_back(l2_1);
	l1.push_back(l2_2);
	l1.push_back(l2_3);

	std::string ser2 = Json::serialize(l1);
	std::string exp2 = readfile("data/strjson/array4.json");
	TEST_ASSERT(exp2, ser2);
}

void
JsonStringSuite::deepObject()
{
	std::map<std::string, std::map<std::string, std::string> > m1;
	std::map<std::string, std::string> values1, values2;
	values1["fst"] = "first it is";
	values1["snd"] = "second it is";
	values1["thd"] = "third it is";

	values2["A"] = "A is 23";
	values2["B"] = "B is larger than C";
	values2["C"] = "C is smaller than A";

	m1["enumeration"] = values1;
	m1["riddle"]      = values2;

	std::string ser = Json::serialize(m1);
	std::string exp = readfile("data/strjson/object3.json");
	TEST_ASSERT(exp, ser);
}

void
JsonStringSuite::mixed()
{
	std::vector<std::map<std::string, Json::value_t> > tv;
	std::map<std::string, Json::value_t> wd, himym, futurama;

	wd["name"]    = std::string("The walking dead");
	wd["rating"]  = 5;
	wd["zombies"] = true;

	himym["name"]    = std::string("How I met your mother");
	himym["rating"]  = 7;
	himym["zombies"] = false;

	futurama["name"]    = std::string("Futurama");
	futurama["rating"]  = 10;
	futurama["zombies"] = true; /* I count Bender. */

	tv.push_back(wd);
	tv.push_back(himym);
	tv.push_back(futurama);

	std::string ser = Json::serialize(tv);
	std::string exp = readfile("data/strjson/mixed1.json");
	TEST_ASSERT(exp, ser);
}

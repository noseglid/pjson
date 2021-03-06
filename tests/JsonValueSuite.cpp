#include "pjtestframework.hpp"
#include "JsonValueSuite.hpp"

#include <pjson/pjson.hpp>
#include <boost/lexical_cast.hpp>

#include <string>

void
JsonValueSuite::run()
{
	std::cout << "Running suite 'JsonValue'.";

	this->validString();
	this->invalidString();
	this->validNumber();
	this->invalidNumber();
	this->validObject();
	this->invalidObject();
	this->validBool();
	this->invalidBool();
	this->validNull();
	this->invalidNull();
	this->validArray();
	this->invalidArray();
	this->getType();
	this->getOperator();
	this->invalidGetOperator();
	this->validNested();
	this->invalidNested();

	this->invalidGet();
	this->objectHasKey();
	this->arrayHasKey();
}

void JsonValueSuite::report()
{
	std::cout << pjreport();
}

void
JsonValueSuite::validString()
{
	std::string json1 = readfile("data/validstring1.json");
	Json::Value p1 = Json::deserialize(json1);
	TEST_ASSERT("My single value string", p1.asString());

	std::string json2 = readfile("data/validstring2.json");
	Json::Value p2 = Json::deserialize(json2);
	TEST_ASSERT("This is a valid \"json\" string", p2.asString());
}

void
JsonValueSuite::invalidString()
{
	std::string json1 = readfile("data/invalidstring1.json");
	TEST_THROWS(Json::deserialize(json1), Json::Exception);

	std::string json2 = readfile("data/invalidstring2.json");
	TEST_THROWS(Json::deserialize(json2), Json::Exception);
}

void
JsonValueSuite::validNumber()
{
	std::string json1 = readfile("data/validnumber1.json");
	Json::Value p1 = Json::deserialize(json1);
	TEST_ASSERT(int(5), p1.asInt());

	std::string json2 = readfile("data/validnumber2.json");
	Json::Value p2 = Json::deserialize(json2);
	TEST_ASSERT(double(85.5), p2.asNumber());

	std::string json3 = readfile("data/validnumber3.json");
	Json::Value p3 = Json::deserialize(json3);
	TEST_ASSERT(double(-0.0674), p3.asNumber());

	int max = std::numeric_limits<int>::max();
	std::string json4(boost::lexical_cast<std::string>(max));
	Json::Value p4 = Json::deserialize(json4);
	TEST_ASSERT(max, p4.asInt());
}

void
JsonValueSuite::invalidNumber()
{
	std::string json1 = readfile("data/invalidnumber1.json");
	TEST_THROWS(Json::deserialize(json1), Json::Exception);

	std::string json2 = readfile("data/invalidnumber2.json");
	TEST_THROWS(Json::deserialize(json2), Json::Exception);
}

void
JsonValueSuite::validObject()
{
	std::string j1 = readfile("data/validobject1.json");
	Json::Value p1 = Json::deserialize(j1);
	TEST_ASSERT(p1.asObject()["key1"].asString(), "val1");

	std::string j2 = readfile("data/validobject2.json");
	Json::Value p2 = Json::deserialize(j2);
	TEST_ASSERT(p2.asObject()["key with \"quotes\""].asString(),
	            "value 2 with ws and \"quotes\"");

	std::string j3 = readfile("data/validobject3.json");
	Json::Value p3 = Json::deserialize(j3);
	TEST_ASSERT(p3.asObject()["key1"].asString(), "val1");
	TEST_ASSERT(p3.asObject()["key2"].asString(), "val2");
	TEST_ASSERT(p3.asObject()["key3"].asString(), "val3");

	std::string j4 = readfile("data/validobject4.json");
	Json::Value p4 = Json::deserialize(j4);
	TEST_ASSERT(p4.asObject()["key1"].asInt(),    123);
	TEST_ASSERT(p4.asObject()["key2"].asNumber(), 12e6);
	TEST_ASSERT(p4.asObject()["key3"].asBool(),   true);
	TEST_ASSERT(p4.asObject()["key4"].asBool(),   false);
	TEST_ASSERT(p4.asObject()["key5"].asString(), "string");
	TEST_ASSERT(p4.asObject()["key6"].asString(), "false");

	std::string j5 = readfile("data/validobject5.json");
	Json::Value p5 = Json::deserialize(j5);
	TEST_ASSERT(p5.asObject()["d1key1"].asObject()["d2key1"].asString(), "d2val1");
	TEST_ASSERT(p5.asObject()["d1key1"].asObject()["d2key2"].asInt(),    23);
	TEST_ASSERT(p5.asObject()["d1key2"].asString(), "d1val2");
	TEST_ASSERT(p5.asObject()["d1key3"].asNumber(), 52.4e6);

	std::string j6 = readfile("data/validobject6.json");
	Json::Value p6 = Json::deserialize(j6);
	TEST_ASSERT(p6.asObject()["enclosing in key }"].asString(), "opening and enclosing in value { }");

	std::string j7 = readfile("data/validobject7.json");
	Json::Value p7 = Json::deserialize(j7);
	TEST_ASSERT(p7["key"].asNumber(), 6);

	std::string j8 = readfile("data/validobject8.json");
	Json::Value p8 = Json::deserialize(j8);
	TEST_ASSERT(p8["key1"].asInt(), -15524);
	TEST_ASSERT(p8["key2"].asInt(), -214);
	TEST_ASSERT(p8["key3"].asInt(), -987);
}

void
JsonValueSuite::invalidObject()
{
	std::string json1 = readfile("data/invalidobject1.json");
	TEST_THROWS(Json::deserialize(json1), Json::Exception);

	std::string json2 = readfile("data/invalidobject2.json");
	TEST_THROWS(Json::deserialize(json2), Json::Exception);

	std::string json3 = readfile("data/invalidobject3.json");
	TEST_THROWS(Json::deserialize(json3), Json::Exception);

	std::string json4 = readfile("data/invalidobject4.json");
	TEST_THROWS(Json::deserialize(json4), Json::Exception);

	std::string json5 = readfile("data/invalidobject5.json");
	TEST_THROWS(Json::deserialize(json5), Json::Exception);
}

void
JsonValueSuite::validBool()
{
	std::string json1 = readfile("data/validbool1.json");
	Json::Value p1 = Json::deserialize(json1);
	TEST_ASSERT(p1.asBool(), true);

	std::string json2 = readfile("data/validbool2.json");
	Json::Value p2 = Json::deserialize(json2);
	TEST_ASSERT(p2.asBool(), false);
}

void
JsonValueSuite::invalidBool()
{
	std::string json1 = readfile("data/invalidbool1.json");
	TEST_THROWS(Json::deserialize(json1), Json::Exception);

	std::string json2 = readfile("data/invalidbool2.json");
	TEST_THROWS(Json::deserialize(json2), Json::Exception);
}

void
JsonValueSuite::validNull()
{
	std::string json1 = readfile("data/validnull1.json");
	Json::Value p1 = Json::deserialize(json1);
	TEST_ASSERT(p1.isNull(), true);
}

void
JsonValueSuite::invalidNull()
{
	std::string json1 = readfile("data/invalidnull1.json");
	TEST_THROWS(Json::deserialize(json1), Json::Exception);
}

void
JsonValueSuite::validArray()
{
	std::string json1 = readfile("data/validarray1.json");
	Json::Value p1 = Json::deserialize(json1);
	TEST_ASSERT(p1.asArray()[0].asString(), "singlevalue");

	std::string json2 = readfile("data/validarray2.json");
	Json::Value p2 = Json::deserialize(json2);
	TEST_ASSERT(p2.asArray()[0].asString(), "multivalue");
	TEST_ASSERT(p2.asArray()[1].isNull(),   true);
	TEST_ASSERT(p2.asArray()[2].asNumber(), 12e9);
	TEST_ASSERT(p2.asArray()[3].asBool(),   false);
	TEST_ASSERT(p2.asArray()[4].asObject()["key1"].asString(), "val1");
	TEST_ASSERT(p2.asArray()[5].asBool() ,  true);
	TEST_ASSERT(p2.asArray()[6].asInt(),    22);

	std::string json3 = readfile("data/validarray3.json");
	Json::Value p3 = Json::deserialize(json3);
	TEST_ASSERT(p3.asArray()[0].asString(), "enclosing ] in value");

	std::string json4 = readfile("data/validarray4.json");
	Json::Value p4 = Json::deserialize(json4);
	TEST_ASSERT(p4.asArray()[0].asInt(), 1);
	TEST_ASSERT(p4.asArray()[1].asInt(), 2);
	TEST_ASSERT(p4.asArray()[2].asInt(), 3);
	TEST_ASSERT(p4.asArray()[3].asInt(), 4);
	TEST_ASSERT(p4.asArray()[4].asInt(), 5);
	TEST_ASSERT(p4.asArray()[5].asInt(), 12e4);
	TEST_ASSERT(p4.asArray()[5].asNumber(), 12e4);
	TEST_ASSERT(p4.asArray()[6].asString(), "string");

	std::string json5 = readfile("data/validarray5.json");
	Json::Value p5 = Json::deserialize(json5);
	TEST_ASSERT(-12, p5[0].asInt());
	TEST_ASSERT(-13, p5[1].asInt());
	TEST_ASSERT(-14, p5[2].asInt());
}

void
JsonValueSuite::invalidArray()
{
	std::string json1 = readfile("data/invalidarray1.json");
	TEST_THROWS(Json::deserialize(json1), Json::Exception);

	std::string json2 = readfile("data/invalidarray2.json");
	TEST_THROWS(Json::deserialize(json2), Json::Exception);

	std::string json3 = readfile("data/invalidarray3.json");
	TEST_THROWS(Json::deserialize(json3), Json::Exception);

	std::string json4 = readfile("data/invalidarray4.json");
	TEST_THROWS(Json::deserialize(json4), Json::Exception);

	std::string json5 = readfile("data/invalidarray5.json");
	TEST_THROWS(Json::deserialize(json5), Json::Exception);
}

void
JsonValueSuite::getType()
{
	std::string json1 = "\"string\"";
	Json::Value p1 = Json::deserialize(json1);
	TEST_ASSERT(Json::JVSTRING,  p1.getType());

	std::string json2 = "10";
	Json::Value p2 = Json::deserialize(json2);
	TEST_ASSERT(Json::JVNUMBER, p2.getType());

	std::string json3 = "10";
	Json::Value p3 = Json::deserialize(json3);
	TEST_ASSERT(Json::JVNUMBER, p3.getType());

	std::string json4 = "false";
	Json::Value p4 = Json::deserialize(json4);
	TEST_ASSERT(Json::JVBOOL, p4.getType());

	std::string json5 = "true";
	Json::Value p5 = Json::deserialize(json5);
	TEST_ASSERT(Json::JVBOOL, p5.getType());

	std::string json6 = "null";
	Json::Value p6 = Json::deserialize(json6);
	TEST_ASSERT(Json::JVNULL, p6.getType());

	std::string json7 = "[1, 1, 2, 3, 5, 8, 13]";
	Json::Value p7 = Json::deserialize(json7);
	TEST_ASSERT(Json::JVARRAY, p7.getType());

	std::string json8 = "{\"a\" : 1, \"b\" : 2}";
	Json::Value p8 = Json::deserialize(json8);
	TEST_ASSERT(Json::JVOBJECT, p8.getType());

	TEST_ASSERT(Json::JVNUMBER, p7.asArray()[2].getType());
	TEST_ASSERT(Json::JVNUMBER, p8.asObject()["a"].getType());
}

void
JsonValueSuite::getOperator()
{
	std::string json1 = readfile("data/validobject4.json");
	Json::Value p1 = Json::deserialize(json1);
	TEST_ASSERT(123,      p1["key1"].asInt());
	TEST_ASSERT(12e6,     p1["key2"].asNumber());
	TEST_ASSERT(true,     p1["key3"].asBool());
	TEST_ASSERT(false,    p1["key4"].asBool());
	TEST_ASSERT("string", p1["key5"].asString());
	TEST_ASSERT("false",  p1["key6"].asString());

	std::string json2 = readfile("data/validarray2.json");
	Json::Value p2 = Json::deserialize(json2);
	TEST_ASSERT("multivalue", p2[0].asString());
	TEST_ASSERT(true,         p2[1].isNull());
	TEST_ASSERT(12e9,         p2[2].asNumber());
	TEST_ASSERT(false,        p2[3].asBool());
	TEST_ASSERT("val1",       p2[4]["key1"].asString());
	TEST_ASSERT(true,         p2[5].asBool());
	TEST_ASSERT(22,           p2[6].asInt());
}

void
JsonValueSuite::invalidGetOperator()
{
	std::string json1 = readfile("data/validobject4.json");
	Json::Value p1 = Json::deserialize(json1);
	TEST_THROWS(p1["does_not_exist"], Json::Exception);

	std::string json2 = readfile("data/validarray1.json");
	Json::Value p2 = Json::deserialize(json2);
	TEST_THROWS(p2[99], Json::Exception);
}

void
JsonValueSuite::validNested()
{
	std::string json1 = readfile("data/validnested1.json");
	Json::Value p1 = Json::deserialize(json1);

	TEST_ASSERT("l2key1", p1[0]["level1-1"]["level2-1-1"].asString());
	TEST_ASSERT("l2key2", p1[0]["level1-2"]["level2-2-1"].asString());

	TEST_ASSERT("l2key1", p1[1]["level1-1"]["level2-1-2"].asString());
	TEST_ASSERT("l2key2", p1[1]["level1-2"]["level2-2-2"].asString());

	TEST_ASSERT(12, p1[2]["arr1"][0]["somekey"]["somekeyagain"].asInt());
	TEST_ASSERT(14, p1[2]["arr1"][1]["somekey2"]["somekeyagain"].asInt());
	TEST_ASSERT(32, p1[2]["arr1"][1]["another"].asInt());

	TEST_ASSERT(13, p1[2]["arr2"][0]["somekey"]["somekeyagain"].asInt());
	TEST_ASSERT(15, p1[2]["arr2"][1]["somekey2"]["somekeyagain"].asInt());
}

void
JsonValueSuite::invalidNested()
{
	std::string json1 = readfile("data/invalidnested1.json");
	TEST_THROWS(Json::deserialize(json1), Json::Exception);
}

void
JsonValueSuite::invalidGet()
{
	std::string json1 = readfile("data/validarray1.json");
	Json::Value v1 = Json::deserialize(json1);
	TEST_THROWS(v1.asBool(), Json::Exception);
	TEST_THROWS(v1.asString(), Json::Exception);
	TEST_THROWS(v1.asObject(), Json::Exception);
	TEST_THROWS(v1.asInt(), Json::Exception);
	TEST_THROWS(v1.asNumber(), Json::Exception);

	std::string json2 = readfile("data/validstring1.json");
	Json::Value v2 = Json::deserialize(json2);
	TEST_THROWS(v2.asBool(), Json::Exception);
	TEST_THROWS(v2.asArray(), Json::Exception);
	TEST_THROWS(v2.asObject(), Json::Exception);
	TEST_THROWS(v2.asInt(), Json::Exception);
	TEST_THROWS(v2.asNumber(), Json::Exception);
}

void
JsonValueSuite::objectHasKey()
{
	std::string json1 = "{ \"mykey\" : 5 }";
	Json::Value v1 = Json::deserialize(json1);

	TEST_ASSERT(true, v1.objectHasKey("mykey"));
	TEST_ASSERT(false, v1.objectHasKey("nokey"));

	std::string jsonstr = "\"mystring\"";
	Json::Value v2 = Json::deserialize(jsonstr);
	TEST_ASSERT(false, v2.objectHasKey("mykey"));
}

void
JsonValueSuite::arrayHasKey()
{
	std::string json1 = "[1, 2, 3, 4]";
	Json::Value v1 = Json::deserialize(json1);

	TEST_ASSERT(true, v1.arrayHasKey(0));
	TEST_ASSERT(true, v1.arrayHasKey(3));
	TEST_ASSERT(false, v1.arrayHasKey(4));
	TEST_ASSERT(false, v1.arrayHasKey(52));

	std::string jsonstr = "\"mystring\"";
	Json::Value v2 = Json::deserialize(jsonstr);
	TEST_ASSERT(false, v2.arrayHasKey(0));
}

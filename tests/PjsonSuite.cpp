#include "pjtestframework.hpp"
#include "PjsonSuite.hpp"

void
PjsonSuite::run()
{
	std::cout << "Running suite 'Pjson'.";

	this->testSerialize();
	this->testDeserialize();
}

void
PjsonSuite::report()
{
	std::cout << pjreport();
}

void
PjsonSuite::testSerialize()
{
	std::map<std::string, int> playersPerTeam;
	playersPerTeam["Counter-Strike"] = 5;
	playersPerTeam["HoN"] = 5;
	playersPerTeam["Soccer"] = 11;

	std::string ser = Json::serialize(playersPerTeam);
	std::string exp = readfile("data/serialize.json");

	TEST_ASSERT(exp, ser);
}

void
PjsonSuite::testDeserialize()
{
	std::string json = readfile("data/deserialize.json");
	Json::Value wot = Json::deserialize(json);

	TEST_ASSERT("Rand al'Thor", wot[0]["name"].asString());
	TEST_ASSERT("The Dragon",   wot[0]["title"].asString());
	TEST_ASSERT(true,           wot[0]["ta'veren"].asBool());

	TEST_ASSERT("Elayne Trakand", wot[1]["name"].asString());
	TEST_ASSERT("Queen of Andor", wot[1]["title"].asString());
	TEST_ASSERT(false,            wot[1]["ta'veren"].asBool());
}

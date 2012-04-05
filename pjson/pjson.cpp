#include "pjson.hpp"

Json::Value
Json::deserialize(std::string json)
{
	return Json::Value(json, Json::Value::MODE_PARSE);
};

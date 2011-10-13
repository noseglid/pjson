#include <pjson/pjson.hpp>

#include <string>
#include <iostream>

int main(void)
{
	std::string strJSON = "{\"action\" : \"update\", \"itemid\" : \"a6fb4e\", \"name\" : \"cdbabe\"}";
	Json::Value j(strJSON);

	Json::Object obj = j.asObject();

	for (Json::Object::const_iterator it = obj.begin(); it != obj.end(); it++) {
		std::string key   = it->first; /* Key is always a string in Json::Object. No need to cast. */
		std::string value = it->second->asString();
		std::cout << key << " : " << value << std::endl;
	}

	return 0;
}

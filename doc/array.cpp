#include <pjson.hpp>

#include <string>
#include <iostream>

int main(void)
{
	std::string strJSON = "[1, 2, 3, 4, 5]";

	Json::Value j(strJSON);

	Json::JsonArray arr = j.asArray();

	for (Json::JsonArray::const_iterator it = arr.begin(); it != arr.end(); it++) {
		std::cout << (*it)->asInt() << std::endl;
	}

	return 0;
}

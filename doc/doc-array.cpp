#include <pjson/pjson.hpp>

#include <string>
#include <iostream>

int main(void)
{
	std::string strJSON = "[1, 2, 3, 4, 5]";

	std::cout << "Intepreting json: '" << strJSON << "'" << std::endl;
	Json::Value j(strJSON);

	Json::Array arr = j.asArray();

	for (Json::Array::const_iterator it = arr.begin(); it != arr.end(); it++) {
		std::cout << (*it)->asInt() << std::endl;
	}

	return 0;
}

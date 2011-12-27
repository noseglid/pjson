#include <pjson/pjson.hpp>

#include <string>
#include <iostream>

int main(void)
{
	std::string strJSON = "[1, 2, 3, 4, 5, \"There are 6 elements, including me\"]";

	std::cout << "Intepreting json: '" << strJSON << "'" << std::endl;
	Json::Value j = Json::deserialize(strJSON);

	Json::Array arr = j.asArray();

	for (int i = 0; i < 6; ++i) {
		Json::Value *v = arr[i];
		switch (v->getType()) {
		case Json::JVSTRING:
			std::cout << v->asString() << std::endl;
			break;
		case Json::JVNUMBER:
			std::cout << v->asNumber() << std::endl;
			break;
		default:
			std::cout << "Unknown type." << std::endl;
		}
	}

	return 0;
}

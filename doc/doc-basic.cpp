#include <pjson/pjson.hpp>

#include <string>
#include <iostream>

int main(void)
{
	/* A JSON string. */
	std::string strJSON = "{\"action\" : \"update\", \"itemid\" : 38, \"cost\" : 12.99}";

	/* Parse the JSON string */
	Json::Value jv = Json::deserialize(strJSON);

	/* We can now use 'jv' to retrieve the values. */
	std::cout << "Action: " << jv["action"].asString() << std::endl;
	std::cout << "  Item: " << jv["itemid"].asInt()    << std::endl;
	std::cout << "  Cost: " << jv["cost"].asNumber()   << std::endl;

	return 0;
}

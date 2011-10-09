#include <pjson/pjson.hpp>

#include <string>
#include <iostream>

int main(void)
{
	/* A JSON string. */
	std::string strJSON = "{\"action\" : \"update\", \"itemid\" : 38, \"cost\" : 12.99}";

	/* Parse the JSON string */
	Json::Value jv(strJSON);

	/* We can now use 'jv' to retrieve the values. */
	std::cout << "Action: " << jv.asObject()["action"]->asString() << std::endl;
	std::cout << "  Item: " << jv.asObject()["itemid"]->asInt()    << std::endl;
	std::cout << "  Cost: " << jv.asObject()["cost"]->asNumber()   << std::endl;

	/*
	 * We can fetch the object and store it in a local variable
	 * For easier access if we need to use it multiple times.
	 */
	Json::Object obj = jv.asObject();

	return 0;
}

#include <pjson/pjson.hpp>

#include <iostream>
#include <vector>

static void print(const Json::Value& v)
{
	std::cout << ", " << v.asInt();
}

int main(void)
{
	std::string strjson = "[ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 ]";
	Json::Value v = Json::deserialize(strjson);

	std::vector<Json::Value> fib = v.asArray();

	std::cout << fib[0].asInt();
	std::for_each(fib.begin() + 1, fib.end(), print);

	std::cout << std::endl;
	return 0;
}

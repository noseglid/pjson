#include <pjson/pjson.hpp>

#include <string>
#include <iostream>

int main(void)
{
	/* The Wheel of Time words per book */
	std::map<std::string, int> words;
	words["New Spring"]           = 121815;
	words["The Eye of the World"] = 305902;
	words["The Great Hunt"]       = 267078;
	words["The Dragon Reborn"]    = 251392;
	words["The Shadow Rising"]    = 393823;

	/* Parse the JSON string */
	std::string json= Json::serialize(words, Json::FORMAT_PRETTY);

	/* ... and print it */
	std::cout << json << std::endl;

	return 0;
}

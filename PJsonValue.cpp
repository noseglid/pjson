#include "PJsonValue.hpp"
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <sstream>

static enum JsonTypes
JsonValueType(char firstchar)
{
	switch(firstchar) {
		case '{': return JVOBJECT;
		case '[': return JVARRAY;
		case '"': return JVSTRING;
		case 'n': return JVNULL;
		case 't':
		case 'f': return JVBOOL;
		default: return JVNUMBER;
	}
}

std::string
PJsonValue::strip(std::string json)
{
	string ret;
	bool insignificant = true;
	for (unsigned int i = 0; i < json.length(); ++i) {
		if ('"' == json[i]) insignificant = !insignificant;
		if (!(insignificant && isspace(json[i]))) ret += json[i];
	}
	return ret;
}

std::string
PJsonValue::unescape(std::string str)
{
	string ret;
	for (unsigned int i = 0; i < str.length(); ++i) {
		if ('\\' != str[i]) ret += str[i];
	}
	return ret;
}

std::string
PJsonValue::extractLiteral(std::string str, size_t pos = 0) throw (PJsonException)
{
	size_t end = pos;
	while(end < str.length()) {
		if (!isalnum(str[end]) && '.' != str[end]) break;
		end++;
	}

	if (end == pos) throw PJsonException("Literal did not start with alphanumeric.");

	return str.substr(pos, end - pos);
}

/**
 * Extracts the string which starts at position pos. It finds which
 * delimiter is used at this position ('{', '[' or '"') and returns
 * the full string enclosed by these characters. If no closing token
 * is found an exception is thrown.
 *
 * If neither of the starting tokens described above is in 'str' at
 * position 'pos', a literal will be assumed and all characters to the
 * first white-space character (as described in RFC4627) will be returned.
 *
 * @param str             The string which contains the literal string
 * @param pos             The position to start at.
 * @param keep_delimiters Keeps the delimiters in the returned string (e.g. { or ")
 * @throws PJsonException
 * @return The extracted string.
 */
std::string
PJsonValue::extract(std::string str,
                    size_t pos = 0,
                    bool keep_delimiters = false) throw (PJsonException)
{
	if (pos >= str.length()) return string();

	char sdelim = str[pos], edelim;
	switch (sdelim) {
		case '{': edelim = '}'; break;
		case '[': edelim = ']'; break;
		case '"': edelim = '"'; break;
		default: return this->extractLiteral(str, pos);
	}

	size_t depth = 1;
	size_t cpos  = pos + 1;
	char current = NULL, previous = NULL;
	std::stringstream ss(str);
	ss.seekg(cpos);
	do {
		previous = current;
		current = ss.get();
		depth += (current == sdelim && sdelim   != edelim);
		depth -= (current == edelim && previous != '\\');
	} while (++cpos <= str.length() && 0 != depth);

	if (edelim != str[cpos - 1]) throw PJsonException("Not enclosed.");

	return str.substr(pos + !keep_delimiters,
	                  cpos - pos - 2*(!keep_delimiters));
}

void
PJsonValue::parse(std::string json) throw (PJsonException)
{
	switch (JsonValueType(json[0])) {
		case JVOBJECT:
			this->parseObject(json);
			break;
		case JVARRAY:
			this->parseArray(json);
			break;
		case JVNUMBER:
			this->parseNumber(json);
			break;
		case JVSTRING:
			this->parseString(json);
			break;
		case JVBOOL:
			this->parseBool(json);
			break;
		case JVNULL:
			this->parseNull(json);
			break;
	}
}

void
PJsonValue::parseString(std::string json) throw (PJsonException)
{
	this->value = this->unescape(this->extract(json));
	this->type  = JVSTRING;
}

void
PJsonValue::parseNumber(std::string json) throw (PJsonException)
{
	try {
		this->value = boost::lexical_cast<float>(json);
	} catch (bad_cast) {
		throw PJsonException("Number value invalid.");
	}
	this->type  = JVNUMBER;
}

void
PJsonValue::parseBool(std::string json) throw (PJsonException)
{
	if ("true" == json) {
		this->value = true;
	} else if ("false" == json) {
		this->value = false;
	} else {
		throw PJsonException("Boolean value invalid.");
	}
	this->type = JVBOOL;
}

void
PJsonValue::parseNull(std::string json) throw (PJsonException)
{
	if ("null" != json) {
		throw PJsonException("Null value invalid.");
	}

	JsonNull null;
	this->value = null;
	this->type  = JVNULL;
}

void
PJsonValue::parseObject(std::string json) throw (PJsonException)
{
	std::string object = this->extract(json);

	JsonObject m;
	unsigned int keystart = 0;
	while(keystart < object.length()) {
		/* Magic number haven... */
		string key   = this->extract(object, keystart);
		string value = this->extract(object, keystart + key.length() + 3, true);
		m[this->unescape(key)] = new PJsonValue(value);
		keystart += key.length() + value.length() + 4;
	}

	this->value = m;
	this->type  = JVOBJECT;
}

void
PJsonValue::parseArray(std::string json) throw (PJsonException)
{
	std::string array = this->extract(json);

	JsonArray a;
	unsigned int valstart = 0;
	while (valstart < array.length()) {
		string value = this->extract(array, valstart, true);
		a.push_back(new PJsonValue(value));
		valstart += value.length() + 1;

		char sep = array[valstart - 1];
		if (sep != ',' && valstart < array.length()) {
			throw PJsonException("Array invalid.");
		}
	}

	this->value = a;
	this->type  = JVARRAY;
}

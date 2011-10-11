#include "JsonValue.hpp"
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <sstream>

static enum Json::Types
ValueType(char firstchar)
{
	switch(firstchar) {
		case '{': return Json::JVOBJECT;
		case '[': return Json::JVARRAY;
		case '"': return Json::JVSTRING;
		case 'n': return Json::JVNULL;
		case 't':
		case 'f': return Json::JVBOOL;
		default:  return Json::JVNUMBER;
	}
}

std::string
Json::Value::strip(std::string json)
{
	std::string ret;
	bool insignificant = true;
	for (unsigned int i = 0; i < json.length(); ++i) {
		if ('"' == json[i]) insignificant = !insignificant;
		if (!(insignificant && isspace(json[i]))) ret += json[i];
	}
	return ret;
}

std::string
Json::Value::unescape(std::string str)
{
	std::string ret;
	for (unsigned int i = 0; i < str.length(); ++i) {
		if ('\\' != str[i]) ret += str[i];
	}
	return ret;
}

std::string
Json::Value::extractLiteral(std::string str, size_t pos = 0) throw (Json::Exception)
{
	size_t end = pos;
	while(end < str.length()) {
		if (!isalnum(str[end]) && '.' != str[end]) break;
		end++;
	}

	if (end == pos) throw Json::Exception("Literal did not start with alphanumeric.");

	return str.substr(pos, end - pos);
}

std::string
Json::Value::extract(std::string str,
                     size_t pos = 0,
                     bool keep_delimiters = false) throw (Json::Exception)
{
	if (pos >= str.length()) return std::string();

	bool instring = false;
	char sdelim = str[pos], edelim;
	switch (sdelim) {
		case '{': edelim = '}'; break;
		case '[': edelim = ']'; break;
		case '"': edelim = '"'; instring = true; break;
		default: return this->extractLiteral(str, pos);
	}

	size_t depth = 1;
	size_t cpos  = pos + 1;
	char current = 0, previous = 0;
	std::stringstream ss(str);
	ss.seekg(cpos);
	do {
		previous = current;
		current  = ss.get();
		if ('"' == current && previous != '\\') instring = !instring;
		if (instring) continue;

		depth += (current == sdelim && sdelim   != edelim);
		depth -= (current == edelim && previous != '\\');
	} while (++cpos < str.length() && 0 != depth);

	if (edelim != str[cpos - 1]) throw Json::Exception("Not enclosed.");

	return str.substr(pos + !keep_delimiters,
	                  cpos - pos - 2*(!keep_delimiters));
}

void
Json::Value::parse(std::string json) throw (Json::Exception)
{
	switch (ValueType(json[0])) {
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
Json::Value::parseString(std::string json) throw (Json::Exception)
{
	this->value = this->unescape(this->extract(json));
	this->type  = JVSTRING;
}

void
Json::Value::parseNumber(std::string json) throw (Json::Exception)
{
	try {
		this->value = boost::lexical_cast<float>(json);
	} catch (std::bad_cast) {
		throw Json::Exception("Number value invalid.");
	}
	this->type  = JVNUMBER;
}

void
Json::Value::parseBool(std::string json) throw (Json::Exception)
{
	if ("true" == json) {
		this->value = true;
	} else if ("false" == json) {
		this->value = false;
	} else {
		throw Json::Exception("Boolean value invalid.");
	}
	this->type = JVBOOL;
}

void
Json::Value::parseNull(std::string json) throw (Json::Exception)
{
	if ("null" != json) {
		throw Json::Exception("Null value invalid.");
	}

	this->type = JVNULL;
}

void
Json::Value::parseObject(std::string json) throw (Json::Exception)
{
	std::string object = this->extract(json);

	Json::Object m;
	unsigned int keystart = 0;
	while(keystart < object.length()) {
		/* Magic number haven... */
		std::string key   = this->extract(object, keystart);
		std::string value = this->extract(object, keystart + key.length() + 3, true);
		m[this->unescape(key)] = new Value(value);
		keystart += key.length() + value.length() + 4;
	}

	this->value = m;
	this->type  = JVOBJECT;
}

void
Json::Value::parseArray(std::string json) throw (Json::Exception)
{
	std::string array = this->extract(json);

	Json::Array a;
	unsigned int valstart = 0;
	while (valstart < array.length()) {
		std::string value = this->extract(array, valstart, true);
		a.push_back(new Value(value));
		valstart += value.length() + 1;

		char sep = array[valstart - 1];
		if (sep != ',' && valstart < array.length()) {
			this->deleteArray(a);
			throw Json::Exception("Array invalid.");
		}
	}

	this->value = a;
	this->type  = JVARRAY;
}

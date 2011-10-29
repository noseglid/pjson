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
Json::Value::minify(std::string json)
{
	std::string ret;
	bool insignificant = true;
	for (unsigned int i = 0; i < json.length(); ++i) {
		if ('"' == json[i]) insignificant = !insignificant;
		if (!(insignificant && isspace(json[i]))) ret += json[i];
	}
	return ret;
}

void
Json::Value::unescape(std::string& str)
{
	size_t pos = 0;
	while (std::string::npos != (pos = str.find('\\', pos))) {
		str.erase(pos, 1);
		pos += 2;
	}
}

void
Json::Value::escape(std::string& str, const char c)
{
	size_t pos = 0;
	while (std::string::npos != (pos = str.find(c, pos))) {
		str.insert(pos, "\\");
		pos += 2;
	}
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
Json::Value::formatStringForOutput(std::string& str)
{
	this->escape(str, '\\');
	this->escape(str, '"');
	str.insert(0, "\"");
	str.append("\"");
}

std::string
Json::Value::strjson(strformat t)
{
	std::string strjson;
	switch (this->type) {
		case JVOBJECT: this->strjsonObject(strjson); break;
		case JVARRAY:  this->strjsonArray(strjson);  break;
		case JVNUMBER: this->strjsonNumber(strjson); break;
		case JVSTRING: this->strjsonString(strjson); break;
		case JVBOOL:   this->strjsonBool(strjson);   break;
		case JVNULL:   this->strjsonNull(strjson);   break;
		default: throw Json::Exception("Type is unknown.");
	}

	switch (t) {
		case FORMAT_PRETTY:                                    break;
		case FORMAT_MINIFIED: strjson = this->minify(strjson); break;
	}

	return strjson;
}

void
Json::Value::strjsonObject(std::string& strjson)
{
	std::string sep = "{\n";
	Json::Object obj = this->asObject();
	typedef Json::Object::const_iterator objit;

	for (objit it = obj.begin(); it != obj.end(); it++) {
		strjson += sep;
		std::string key = it->first;
		this->formatStringForOutput(key);

		std::string value = it->second->strjson();
		strjson += "\t" + key + " : " + value;
		sep = ",\n";
	}

	strjson += "\n}\n";
}

void
Json::Value::strjsonArray(std::string& strjson)
{
	std::string sep = "[\n";
	Json::Array arr = this->asArray();
	typedef Json::Array::const_iterator arrit;

	for (arrit it = arr.begin(); it != arr.end(); it++) {
		strjson += sep + "\t" + (*it)->strjson();
		sep = ",\n";
	}

	strjson += "\n]\n";
}

void
Json::Value::strjsonNumber(std::string& strjson)
{
	if (this->value.type() == typeid(Json::Int)) {
		strjson = boost::lexical_cast<std::string>(this->asInt());
	} else {
		strjson = boost::lexical_cast<std::string>(this->asNumber());
	}
}

void
Json::Value::strjsonString(std::string& strjson)
{
	strjson = this->asString();
	this->formatStringForOutput(strjson);
}

void
Json::Value::strjsonBool(std::string& strjson)
{
	strjson = (this->asBool() ? "true" : "false");
}

void
Json::Value::strjsonNull(std::string& strjson)
{
	strjson = "null";
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
	std::string str = this->extract(json);
	this->unescape(str);

	this->value = str;
	this->type  = JVSTRING;
}

void
Json::Value::parseNumber(std::string json) throw (Json::Exception)
{
	this->type = JVNUMBER;

	try {
		this->value = boost::lexical_cast<Json::Int>(json);
		return;
	} catch (std::bad_cast) {}

	try {
		this->value = boost::lexical_cast<Json::Number>(json);
		return;
	} catch (std::bad_cast) {}

	throw Json::Exception("Number value invalid.");
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
		std::string key = this->extract(object, keystart);
		size_t klength  = key.length();

		std::string value = this->extract(object, keystart + key.length() + 3, true);
		size_t vlength    = value.length();
		this->unescape(key);

		m[key] = new Value(value, Value::MODE_PARSE);
		keystart += klength + vlength + 4;
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
		a.push_back(new Value(value, Value::MODE_PARSE));
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

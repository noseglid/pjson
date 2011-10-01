#ifndef _PJSONVALUE_H_
#define _PJSONVALUE_H_

#include "PJsonException.hpp"

#include "boost/variant.hpp"

#include <string>
#include <map>
#include <vector>

using namespace std;

class PJsonValue;

typedef void* JsonNull;
typedef map<string, PJsonValue*> JsonObject;
typedef vector<PJsonValue*> JsonArray;

typedef boost::variant<string,
                       float,
                       bool,
                       JsonNull,
                       JsonObject,
                       JsonArray> JsonValue;

enum JsonTypes {
	JVOBJECT,
	JVARRAY,
	JVNUMBER,
	JVSTRING,
	JVFALSE,
	JVNULL,
	JVTRUE,
};

class PJsonValue
{
	private:
		JsonValue value;
		JsonTypes type;

		string strip(string);
		string unescape(string);
		string extract(string, size_t, bool) throw (PJsonException);
		string extractLiteral(string, size_t) throw (PJsonException);
		void parse(string) throw (PJsonException);
		void parseString(string) throw (PJsonException);
		void parseNumber(string) throw (PJsonException);
		void parseBool(string) throw (PJsonException);
		void parseNull(string) throw (PJsonException);
		void parseObject(string) throw (PJsonException);
		void parseArray(string) throw (PJsonException);

	public:
		PJsonValue(string json) throw (PJsonException)
		{
			json = this->strip(json);
			this->parse(json);
		};

		~PJsonValue()
		{
			switch (this->type) {
			case JVOBJECT:
			{
				JsonObject o = this->asMap();
				for (JsonObject::iterator it = o.begin(); it != o.end(); it++) {
					delete it->second;
				}
				break;
			}
			case JVARRAY:
			{
				JsonArray a = this->asArray();
				for (JsonArray::iterator it = a.begin(); it != a.end(); it++) {
					delete *it;
				}
				break;
			}
			default:
				break;
			}
		}

		template <class T>
		T get() {
			return boost::get<T>(this->value);
		}

		JsonArray asArray()
		{
			return this->get<JsonArray>();
		}

		JsonObject asMap()
		{
			return this->get<JsonObject>();
		}

		int asInt()
		{
			return this->get<float>();
		}

		float asFloat()
		{
			return this->get<float>();
		}

		bool asBool()
		{
			return this->get<bool>();
		}

		string asString()
		{
			return this->get<string>();
		};

		const char *asCString()
		{
			return this->get<string>().c_str();
		};

		bool isNull()
		{
			return NULL == this->get<JsonNull>();
		};
};

#endif

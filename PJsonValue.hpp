#ifndef _PJSONVALUE_H_
#define _PJSONVALUE_H_

#include "PJsonException.hpp"
#include "boost/variant.hpp"
#include <string>
#include <map>
#include <vector>

class PJsonValue;

typedef void* JsonNull;
typedef std::map<std::string, PJsonValue*> JsonObject;
typedef std::vector<PJsonValue*> JsonArray;

typedef boost::variant<std::string,
                       float,
                       bool,
                       JsonObject,
                       JsonArray> JsonValue;

enum JsonTypes {
	JVOBJECT,
	JVARRAY,
	JVNUMBER,
	JVSTRING,
	JVBOOL,
	JVNULL
};

class PJsonValue
{
	private:
		JsonValue value;
		JsonTypes type;

		std::string strip(std::string);
		std::string unescape(std::string);
		std::string extract(std::string, size_t, bool) throw (PJsonException);
		std::string extractLiteral(std::string, size_t) throw (PJsonException);
		void parse(std::string) throw (PJsonException);
		void parseString(std::string) throw (PJsonException);
		void parseNumber(std::string) throw (PJsonException);
		void parseBool(std::string) throw (PJsonException);
		void parseNull(std::string) throw (PJsonException);
		void parseObject(std::string) throw (PJsonException);
		void parseArray(std::string) throw (PJsonException);

		static void deleteObject(JsonObject obj)
		{
			for (JsonObject::iterator it = obj.begin(); it != obj.end(); it++) {
				delete it->second;
			}
		}
		static void deleteArray(JsonArray arr)
		{
			for (JsonArray::iterator it = arr.begin(); it != arr.end(); it++) {
				delete *it;
			}
		}

	public:
		PJsonValue(std::string json) throw (PJsonException)
		{
			json = this->strip(json);
			this->parse(json);
		};

		~PJsonValue()
		{
			switch (this->type) {
			case JVOBJECT:
				this->deleteObject(this->asMap());
				break;
			case JVARRAY:
				this->deleteArray(this->asArray());
				break;
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

		std::string asString()
		{
			return this->get<std::string>();
		};

		bool isNull()
		{
			return JVNULL == this->type;
		};
};

#endif

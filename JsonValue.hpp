#ifndef _JSONVALUE_H_
#define _JSONVALUE_H_

#include "JsonException.hpp"
#include <boost/variant.hpp>
#include <string>
#include <map>
#include <vector>

namespace Json {
	class Value;

	typedef std::string JsonString;
	typedef double JsonNumber;
	typedef bool JsonBool;
	typedef std::map<std::string, Value*> JsonObject;
	typedef std::vector<Value*> JsonArray;

	enum Types {
		JVOBJECT,
		JVARRAY,
		JVNUMBER,
		JVSTRING,
		JVBOOL,
		JVNULL
	};

	class Value
	{
		private:
			boost::variant<JsonString,
	                       JsonNumber,
	                       JsonBool,
	                       JsonObject,
	                       JsonArray> value;
			Types type;

			std::string strip(std::string);
			std::string unescape(std::string);
			std::string extract(std::string, size_t, bool) throw (Json::Exception);
			std::string extractLiteral(std::string, size_t) throw (Json::Exception);
			void parse(std::string) throw (Json::Exception);
			void parseString(std::string) throw (Json::Exception);
			void parseNumber(std::string) throw (Json::Exception);
			void parseBool(std::string) throw (Json::Exception);
			void parseNull(std::string) throw (Json::Exception);
			void parseObject(std::string) throw (Json::Exception);
			void parseArray(std::string) throw (Json::Exception);

			static void deleteObject(JsonObject obj)
			{
				for (JsonObject::iterator it = obj.begin(); it != obj.end(); it++) {
					delete it->second;
				}
			};

			static void deleteArray(JsonArray arr)
			{
				for (JsonArray::iterator it = arr.begin(); it != arr.end(); it++) {
					delete *it;
				}
			};

		public:
			Value(std::string json) throw (Json::Exception)
			{
				json = this->strip(json);
				this->parse(json);
			};

			~Value()
			{
				switch (this->type) {
				case JVOBJECT:
					this->deleteObject(this->asObject());
					break;
				case JVARRAY:
					this->deleteArray(this->asArray());
					break;
				default:
					break;
				}
			};

			template <class T>
			T get() {
				return boost::get<T>(this->value);
			};

			JsonArray asArray()
			{
				return this->get<JsonArray>();
			};

			JsonObject asObject()
			{
				return this->get<JsonObject>();
			};

			int asInt()
			{
				return this->get<double>();
			};

			JsonNumber asNumber()
			{
				return this->get<double>();
			};

			JsonBool asBool()
			{
				return this->get<bool>();
			};

			JsonString asString()
			{
				return this->get<std::string>();
			};

			bool isNull()
			{
				return JVNULL == this->type;
			};
	};
}

#endif

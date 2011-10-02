#ifndef _JSONVALUE_H_
#define _JSONVALUE_H_

#include "JsonException.hpp"
#include <boost/variant.hpp>
#include <string>
#include <map>
#include <vector>

/// Default namespace for the <em>pjson</em> library.
/**
 * The namespace which any class of the pjson library
 * is a part of.
 * */
namespace Json {

	class Value;

	/**
	 * The available JSON types.
	 */
	enum Types {
		/** Object type */
		JVOBJECT,
		/** Array type */
		JVARRAY,
		/** Number type (double, int) */
		JVNUMBER,
		/** String type */
		JVSTRING,
		/** Bool type (true, false) */
		JVBOOL,
		/** Null type (null) */
		JVNULL
	};


	/**
	 * A representation of a JSON string.
	 */
	typedef std::string JsonString;

	/**
	 * A representation of a JSON number.
	 */
	typedef double JsonNumber;

	/**
	 * A representation of a JSON boolean; true or false.
	 */
	typedef bool JsonBool;

	/**
	 * A representation of a JSON object; key, value pairs.
	 */
	typedef std::map<std::string, Value*> JsonObject;

	/**
	 * A representation of a JSON array; consecutive values.
	 */
	typedef std::vector<Value*> JsonArray;

	/// The main class representing a JSON value.
	/**
	 * Representation of one JSON value.
	 *
	 * Each value can be either a string, number, true, false, null
	 * or one of the structure types object or array.
	 *
	 * - A string can be: "mystring".
	 * - A number may be: 4e-3 (0.004)
	 * - The literals are: true, false or null (note lower case).
	 *
	 * An array is several values listed. The value may be another array or object.
	 *
	 * @code
	 * [ "value1", 12, false ]
	 * @endcode
	 * @code
	 * [ [ "valx1", "valx2" ], [ "valy1", "valy2" ] ]
	 * @endcode
	 *
	 * An object is several values, identified by a string key.
	 * The value may be another array or object.
	 *
	 * @code
	 * {
	 *   "key1" : "val1"
	 * }
	 * @endcode
	 * @code
	 * {
	 *   "arr" : [1, 2, 3],
	 *   "obj" :
	 *   {
	 *     "first"  : 1,
	 *     "second" : 2,
	 *     "third"  : 3
	 *   }
	 * }
	 * @endcode
	 */
	class Value
	{
		public:

			/**
			 * Parse a json string. This provides an easy to use interface
			 * to fetch values and structures.
			 *
			 * @param json The json object as a string.
			 * @throws Json::Exception If the string can not be interpreted as json.
			 * @returns A representation of the json object.
			 */
			Value(std::string json) throw (Json::Exception)
			{
				json = this->strip(json);
				this->parse(json);
			};

			/**
			 * Deletes this Value, and all values this may hold.
			 * If this, for example, is an array, it will loop
			 * over all the values the array holds and delete them one by one.
			 */
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

			/**
			 * Fetches the value, casted to class T. Unless needed for specific
			 * reasons (such as dynamic types), use the 'asX()' functions instead.
			 *
			 * @throws std::bad_cast If the value cant be casted to T.
			 * @returns The current value.
			 */
			template <class T>
			T get() {
				return boost::get<T>(this->value);
			};

			/**
			 * Get the value as a JsonArray.
			 *
			 * @return The value as an array.
			 * @see JsonArray
			 * @see get()
			 */
			JsonArray asArray()
			{
				return this->get<JsonArray>();
			};

			/**
			 * Get the value as a JsonObject.
			 *
			 * @return The value as an object.
			 * @see JsonObject
			 * @see get()
			 */
			JsonObject asObject()
			{
				return this->get<JsonObject>();
			};

			/**
			 * Get the value as an integer.
			 *
			 * @return The JSON number as an integer.
			 * @see get()
			 */
			int asInt()
			{
				return this->get<double>();
			};

			/**
			 * Get the value as a number.
			 *
			 * @return The value as a number.
			 * @see JsonNumber
			 * @see get()
			 */
			JsonNumber asNumber()
			{
				return this->get<double>();
			};

			/**
			 * Get the value as a boolean.
			 *
			 * @return The value as a boolean.
			 * @see JsonBool
			 * @see get()
			 */
			JsonBool asBool()
			{
				return this->get<bool>();
			};

			/**
			 * Get the value as a string.
			 *
			 * @return The value as a string.
			 * @see JsonString
			 * @see get()
			 */
			JsonString asString()
			{
				return this->get<std::string>();
			};

			/**
			 * Determines whether this JSON value is null or not.
			 * Only the JSON literal 'null' will be considered as null.
			 *
			 * @return True if JSON value is null, false otherwise.
			 */
			bool isNull()
			{
				return JVNULL == this->type;
			};

		private:
			boost::variant<JsonString,
	                       JsonNumber,
	                       JsonBool,
	                       JsonObject,
	                       JsonArray> value;
			Types type;

			/**
			 * Strips the string, removing any insignificant characters
			 * from a json point of view (insignificant white-spaces).
			 *
			 * @param json The json string to strip.
			 * @returns The stripped string
			 */
			std::string strip(std::string);

			/**
			 * Remove any escape characters (\) from the string.
			 *
			 * @param std::string The string to remove escape characters from.
			 * @returns The unescaped string.
			 */
			std::string unescape(std::string);

			/**
			 * Extracts a literal from string str starting at position pos.
			 * The literal extracted will be as defined in RFC4627.
			 * If pos in str does is nothing which could be a literal,
			 * an exception is thrown.
			 *
			 * @param std::string The string from where the literal should be extraced.
			 * @param size_t The position the literal starts at.
			 * @throws Json::Exception
			 * @returns The extracted literal.
			 */
			std::string extractLiteral(std::string, size_t) throw (Json::Exception);

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
			 * @param std::string The string which contains the literal string
			 * @param size_t      The position to start at.
			 * @param bool        Keeps the delimiters in the returned string (e.g. { or ")
			 * @throws Json::Exception
			 * @return The extracted string.
			 */
			std::string extract(std::string, size_t, bool) throw (Json::Exception);
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
	};
}

#endif

#ifndef __JSONVALUE_H__
#define __JSONVALUE_H__

#include "JsonException.hpp"

#include <boost/variant.hpp>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

/// Default namespace for the <em>pjson</em> library.
/**
 * The namespace which any class of the pjson library
 * is a part of.
 * */
namespace Json {

	class Value;
	class Builder;

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
	typedef std::string String;

	/**
	 * A representation of a JSON number.
	 */
	typedef double Number;

	/**
	 * A representation of a JSON boolean; true or false.
	 */
	typedef bool Bool;

	/**
	 * A representation of a JSON object; key, value pairs.
	 */
	typedef std::map<std::string, Value*> Object;

	/**
	 * A representation of a JSON array; consecutive values.
	 */
	typedef std::vector<Value*> Array;

	/// The main class representing a JSON value.
	/**
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
	 *
	 * @see value_t
	 */
	class Value
	{
		friend class Builder;

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
			 * Get the type of this value,(e.g. JVARRAY or JVNUMBER). This can
			 * be used to determine which 'asT()' function you can use to
			 * retrieve the value.
			 *
			 * @returns The type as defined by Json::Types
			 * @see Json::Types
			 */
			Json::Types
			getType()
			{
				return this->type;
			}

			/**
			 * Fetches the value, casted to class T. Unless needed for specific
			 * reasons (such as dynamic types), use the 'asT()' functions instead.
			 *
			 * @throws std::bad_cast If the value cant be casted to T.
			 * @returns The current value.
			 */
			template <class T>
			T get() {
				return boost::get<T>(this->value);
			};

			/**
			 * Fetches the value defined by 'key' in the Object
			 * this value represents.
			 *
			 * @note This Json::Value must represent an object.
			 *
			 * @param key The key to use to retrieve the value.
			 * @throws Json::Exception If the string is not a key in the object.
			 * @returns The value identified by key.
			 */
			Value& operator[](const char* key) throw (Json::Exception)
			{
				Object obj          = this->asObject();
				Object::iterator it = obj.find(key);

				if (it == obj.end()) {
					throw Json::Exception("Key does not exist in object.");
				}

				return *it->second;
			};

			/**
			 * Fetches the value defined by key in the Array
			 * this value represents.
			 *
			 * @note This Json::Value must represent an array.
			 *
			 * The key is indexed from 0 to n-1, where n is the number of
			 * elements in the array. (see std::vector).
			 *
			 * @param key The key to use to retrieve the value.
			 * @throws Json::Exception If the index is outside of the Array bounds.
			 * @returns The value identified by key.
			 */
			Value& operator[](int key) throw (Json::Exception)
			{
				try {
					return *this->asArray().at(key);
				} catch (std::out_of_range) {
					throw Json::Exception("Out of array bounds.");
				}
			};

			/**
			 * Get the value as an Array.
			 *
			 * @return The value as an array.
			 * @see Json::Array
			 * @see get()
			 */
			Json::Array asArray()
			{
				return this->get<Json::Array>();
			};

			/**
			 * Get the value as a JsonObject.
			 *
			 * @return The value as an object.
			 * @see Json::Object
			 * @see get()
			 */
			Json::Object asObject()
			{
				return this->get<Json::Object>();
			};

			/**
			 * Get the value as an integer.
			 *
			 * @note If the value was stored as a double,
			 *       several significant digits may have been truncated.
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
			 * @see Json::Number
			 * @see get()
			 */
			Json::Number asNumber()
			{
				return this->get<double>();
			};

			/**
			 * Get the value as a boolean.
			 *
			 * @return The value as a boolean.
			 * @see Json::Bool
			 * @see get()
			 */
			Json::Bool asBool()
			{
				return this->get<bool>();
			};

			/**
			 * Get the value as a string.
			 *
			 * @return The value as a string.
			 * @see Json::String
			 * @see get()
			 */
			Json::String asString()
			{
				return this->get<Json::String>();
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

			/**
			 * Returns a JSON string representation of this value.
			 * The string is a valid JSON string according to RFC4627.
			 * It can be used to transmit information to another JSON
			 * compatible recipient.
			 *
			 * @return std::string The string representation of this JSON value.
			 */
			std::string str()
			{
				return std::string("say what");
			}

			static Json::Types typeByValue(Json::value_t v)
			{
				if (v.type() == typeid(Json::String)) {
					return Json::JVSTRING;
				} else if (v.type() == typeid(Json::Bool)) {
					return Json::JVBOOL;
				} else if (v.type() == typeid(Json::Object)) {
					return Json::JVOBJECT;
				} else if (v.type() == typeid(Json::Array)) {
					return Json::JVARRAY;
				}

				return Json::JVNUMBER;
			}

		private:
			boost::variant<Json::String,
			               Json::Number,
			               Json::Bool,
			               Json::Object,
			               Json::Array> value;
			Json::Types type;

			/**
			 * Quick instance of value. In private section to not
			 * expose unwanted usage. The caller must know what to
			 * do with the instance as it will not give anything
			 * interesting straight off.
			 */
			Value(Json::value_t v, Json::Types t)
			{
				this->value = v;
				this->type  = t;
			}

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

			static void deleteObject(Json::Object obj)
			{
				for (Json::Object::iterator it = obj.begin(); it != obj.end(); it++) {
					delete it->second;
				}
			};

			static void deleteArray(Json::Array arr)
			{
				for (Json::Array::iterator it = arr.begin(); it != arr.end(); it++) {
					delete *it;
				}
			};
	};
}

#endif

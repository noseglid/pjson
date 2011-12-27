#ifndef __JSONVALUE_H__
#define __JSONVALUE_H__

#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#include "JsonException.hpp"

/// Default namespace for the <em>pjson</em> library.
/**
 * The namespace which any class of the pjson library
 * is a part of.
 * */
namespace Json {
	class Value;
	class Builder;

	enum strformat {
		/**
		 * The string will be pretty formatted, suitable for printing.
		 */
		FORMAT_PRETTY,

		/**
		 * Minified format, all insignificant whitespaces will be removed,
		 * suitable for transmitting.
		 */
		FORMAT_MINIFIED
	};

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
	 * Representation of a JSON string as common in C.
	 */
	typedef const char* CString;

	/**
	 * A representation of a JSON number.
	 */
	typedef double Number;

	/**
	 * An integer. This is not part of the JSON standard but
	 * has its own type for increased precision in integers in C++.
	 */
	typedef int Int;

	/**
	 * A representation of a JSON boolean; true or false.
	 */
	typedef bool Bool;

	/**
	 * A representation of a NULL value
	 */
	struct NullValue {};
	typedef NullValue Null;

	/**
	 * A representation of a JSON object; key, value pairs.
	 */
	typedef std::map<std::string, Json::Value*> Object;

	/**
	 * A representation of a JSON array; consecutive values.
	 */
	typedef std::vector<Json::Value*> Array;

	/**
	 * Storage of a JSON value. It can be either of the
	 * types defined in the variant.
	 */
	typedef boost::variant<Json::String,
	                       Json::CString,
	                       Json::Number,
	                       Json::Int,
	                       Json::Bool,
	                       Json::NullValue,
	                       Json::Object,
	                       Json::Array> value_t;

	/// The main class representing a JSON value.
	/**
	 * @note Instances of this class can be obtained using Json::Builder or Json::deserialize.
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
	 *
	 * @see value_t
	 */
	class Value
	{
		friend class Builder;
		friend Json::Value deserialize(std::string);
		friend Json::Value deserialize(const char*);
		template <class T> friend std::string serialize(T) throw (Json::Exception);
		friend std::string serialize(Json::Value);

		/**
		 * Formats which can be used when retrieving
		 * a string representation of this instance.
		 */
		public:

			/**
			 * Copies any previously defined Value.
			 *
			 * @param v The Value to copy.
			 */
			Value(const Value& v);

			/**
			 * Deletes this Value, and all values this may hold.
			 * If, for example, this is an array, it will loop
			 * over all the values the array holds and delete them one by one.
			 */
			~Value();

			/**
			 * Get the type of this value,(e.g. JVARRAY or JVNUMBER). This can
			 * be used to determine which 'asT()' function you can use to
			 * retrieve the value.
			 *
			 * @returns The type as defined by Json::Types
			 * @see Json::Types
			 */
			Json::Types
			getType() const;

			/**
			 * Handles assignment properly from one
			 * Value to another. All values are copied, including
			 * Arrays and Objects. The newly created Value needs to
			 * be deallocated seperatly.
			 *
			 * @param v The Value this is assigned to.
			 * @returns The newly assigned value.
			 */
			Json::Value& operator=(const Json::Value& v);


			/**
			 * Fetches the value, casted to class T. Unless needed for specific
			 * reasons (such as dynamic types), use the 'asT()' functions instead.
			 *
			 * @tparam T The type this value should be casted to. Must be
			 *           one of Json::value_t or and exception will be thrown.
			 * @throws Json::Exception If the value cant be casted to T.
			 * @returns The current value in specified type.
			 */
			template <class T> T
			get() const throw (Json::Exception);

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
			Value&
			operator[](const char*) const throw (Json::Exception);

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
			Value& operator[](int key) const throw (Json::Exception);

			/**
			 * Get the value as an Array.
			 *
			 * @returns The value as an array.
			 * @throws Json::Exception If current value cannot be
			 *                         interpreted as an Array.
			 * @see Json::Array
			 * @see get()
			 * @returns Json::Array The array this value represents
			 */
			Json::Array asArray() const throw (Json::Exception);

			/**
			 * Get the value as a JsonObject.
			 *
			 * @returns The value as an object.
			 * @throws Json::Exception If current value cannot be
			 *                         interpreted as an Object
			 * @see Json::Object
			 * @see get()
			 */
			Json::Object asObject() const throw (Json::Exception);

			/**
			 * Get the value as an integer.
			 *
			 * @returns The JSON number as an integer.
			 * @throws Json::Exception If current value cannot be
			 *                         interpreted as an integer.
			 * @see get()
			 */
			Json::Int asInt() const throw (Json::Exception);

			/**
			 * Get the value as a number.
			 *
			 * @returns The value as a number.
			 * @throws Json::Exception If current value cannot be
			 *                        interpreted as a number.
			 * @see Json::Number
			 * @see get()
			 */
			Json::Number asNumber() const throw (Json::Exception);

			/**
			 * Get the value as a boolean.
			 *
			 * @returns The value as a boolean.
			 * @throws Json::Exception If current value cannot be
			 *                         interpreted as a boolean.
			 * @see Json::Bool
			 * @see get()
			 */
			Json::Bool asBool() const throw (Json::Exception);

			/**
			 * Get the value as a string.
			 *
			 * @returns The value as a string.
			 * @throws Json::Exception If current value cannot be
			 *                         interpreted as a string
			 * @see Json::String
			 * @see get()
			 */
			Json::String asString() const throw (Json::Exception);

			/**
			 * Determines whether this JSON value is null or not.
			 * Only the JSON literal 'null' will be considered as null.
			 *
			 * @return True if JSON value is null, false otherwise.
			 */
			bool isNull() const;

		private:
			/**
			 * The mode with which this class can be instantiated.
			 *
			 * @see Value(std::string, cmode)
			 */
			enum cmode {
				MODE_PARSE
			};

			/**
			 * The value held by this instance.
			 */
			Json::value_t value;

			/**
			 * The type of the value held by this instance.
			 */
			Json::Types type;


			/**
			 * Creates a Value using specified mode.
			 *  - MODE_PARSE: Provided string is a JSON string.
			 *
			 *  @param json The json string
			 *  @param m    The mode of how to interpret the JSON string.
			 */
			Value(std::string json, cmode m) throw (Json::Exception);

			/**
			 * Creates a Value and sets it to the provided value.
			 * The type is derived from the input value.
			 *
			 * @param v The value this instance should represent.
			 */
			Value(Json::value_t v);

			/**
			 * Creates a NULL value. This sets the type to 'NULL',
			 * and leaves the actual value undefined.
			 */
			Value();

			/**
			 * Tells the type of a Json::value_t.
			 *
			 * @param v The Json::value_t to check type for.
			 * @returns The type of the provided Json::value_t
			 * @see getType()
			 * @see Json::Types
			 */
			static Json::Types typeByValue(Json::value_t v) throw (Json::Exception);

			/**
			 * Minifies the JSON string, removing any insignificant characters
			 * from a json point of view (insignificant white-spaces).
			 *
			 * @param json The JSON string to minify.
			 * @returns The minified string.
			 */
			std::string minify(std::string) const;

			/**
			 * Remove any escape characters (\) from the string.
			 *
			 * @param std::string The string to remove escape characters from.
			 * @returns The unescaped string.
			 */
			void unescape(std::string&) const;

			/**
			 * Prepends any occurance of c with an escape character (\).
			 *
			 * @note This changes the input variable.
			 *
			 * @param strjson The string to escape.
			 * @param c       The character which needs to be escaped.
			 */
			void escape(std::string&, const char) const;

			/**
			 * Returns a JSON string representation of this value.
			 * The string is a valid JSON string according to RFC4627.
			 * It can be used to transmit information to another JSON
			 * compatible recipient.
			 *
			 * @param t The format to return. See strformat for allowed values.
			 * @returns std::string The string representation of this JSON value.
			 */
			std::string strjson(strformat t = FORMAT_PRETTY) const;

			void formatStringForOutput(std::string&) const;

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

			void strjsonObject(std::string&, size_t) const;
			void strjsonArray(std::string&, size_t) const;
			void strjsonNumber(std::string&) const;
			void strjsonString(std::string&) const;
			void strjsonBool(std::string&) const;
			void strjsonNull(std::string&) const;

			/**
			 * Copies a provided value into this.
			 *
			 * @param v The value to copy.
			 */
			void copy(const Value& v);

			static void deleteObject(Json::Object obj);
			static void deleteArray(Json::Array arr);
	};
}

#endif

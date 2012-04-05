#ifndef __PJSON_HPP__
#define __PJSON_HPP__

/** @mainpage
 * @section intro Introduction to pjson
 * The pjson library is intended to be a fast and easy to use JSON
 * interpreter. It turns any valid JSON string into various container types
 * as std:string, int, std::vector and std::map. Mainly two functions are
 * the base of the interface; Json::serialize and Json::deserialize.
 *
 * This library follows the JSON definition in RFC4627.
 *
 * @section quickuse Quick start
 *
 * Here is a quick example to get you started - more detailed tutorials are below.
 * @include doc-basic.cpp
 * @include doc-basic.out
 *
 *   - For more on objects see \ref doc-object.
 *   - For more on arrays see \ref doc-array.
 *
 * @section Tutorial
 * Several short tutorial of how to work with pjson is listed below.
 *
 * @subsection tut-basic Basic tutorial
 *
 *   - @ref doc-strjson
 *   - @ref doc-value
 *
 * @subsection tut-advances In-depth tutorial
 *
 *   - To be written...
 */

/** @page doc-array Using Json Array
 * An Array is 0 or more consecutive values enclosed by the delmiters '[' and ']'.
 * @code
 * [ "value1", "value2", 12 ]
 * @endcode
 * These are represented in the pjson library by std::vector<Json::Value*>.
 * Take a look at Json::Array.
 *
 * These can be used just as you would use any normal vector in C++.
 * @section Example
 * @include doc-array.cpp
 * @include doc-array.out
 */

/** @page doc-object Using Json Object
 * A json object is a key-value paired container. The key is always a string
 * and the value can be any Json value (including other objects and arrays).
 *
 * An object is 0 or more key, value pairs enclosed by the delimiters '{' and '}'.
 * @code
 * {
 *   "key1", "value1",
 *   "key2", 12
 *   "key3", false
 * }
 * @endcode
 *
 * The keys must be a string, the value may be any JSON value (including numbers
 * strings, literals, arrays etc. Even other objects)
 *
 * An object is represented in the pjson library by
 * std::map<Json::String, Json::Value*>. Take a look at Json::Object.
 * All normal STL functions for this structures apply
 *
 * @section Example
 * @include doc-object.cpp
 * @include doc-object.out
 */

/** @page doc-strjson Serializing: Converting built-in types to JSON strings
 * Serializing (also deflating or marshalling) built-in types is done using the Json::serialize function.
 *
 * Json::serialize takes two arguments - the first is the container you wish to serialize into
 * a JSON string. The second is how to format the string.
 *
 *   - @b Container Almost any container can be serialized. The containers may contain almost any
 *        types including additional containers or primitive types.
 *   - @b Format Two formats are supported; pretty or minified.
 *
 * @section formatting Formatting
 * The output can be formatted in two different ways; pretty or minified.
 *
 * @subsection formatting-pretty Pretty formatting
 * Pretty formatting can be used for debugging purposes or when
 * you want to quickly present the data. Note that all the string
 * is still a valid JSON string, meaning all delimiters, quotations, etc.
 * will be in the string.
 *
 * Here is a simple example of how to serialize a std::map<std::string, int>, containing
 * my favorite book series and the number of words in each book.
 *
 * @include doc-strjson-pretty.cpp
 * @include doc-strjson-pretty.out
 *
 * @subsection formatting-minifed Minified formatting
 * Minified formatting is useful for transmitting. All insignificant white-spaces have
 * been removed which reduces the number of bytes the string consist of. This is very
 * important as the size of the data structures increase. The resulting string is (of course)
 * also a valid JSON string.
 *
 * Here is the same example as above, only now we have left out the formatting argument so it takes
 * the default argument @c Json::FORMAT_MINIFED (of course we could've called the function
 * with this argument to get the very same result).
 *
 * @include doc-strjson-minified.cpp
 * @include doc-strjson-minified.out
 */

/** @page doc-value Deserializing: Converting JSON strings to built-in types
 * Deserializing (also inflating, unserialize or unmarshalling) JSON strings is done using the Json::deserialize function.
 *
 * Json::deserialize takes only one argument; the JSON string which should be parsed into a built-in type.
 *
 *   - @b JSON @b string A string which follows RFC4627.
 *
 * Using deserialize is really straight forward. We will start with a simple example.
 *
 * @include doc-deserialize.cpp
 * @include doc-deserialize.out
 *
 *  - Here, we are creating a simple JSON string, which actually is the famous
 *    <a href="http://en.wikipedia.org/wiki/Fibonacci_number">fibonacci sequence</a>.
 *  - Next we utilize the deserialize function which gives us a Json::Value to work with.
 *  - Next we're using the std::for_each algorithm to print all the values.
 *  - Easy, no?
 *
 */

/**
 * @example doc-basic.cpp
 * @example doc-array.cpp
 * @example doc-object.cpp
 */

#include "pjson/JsonValue.hpp"
#include "pjson/JsonBuilder.hpp"
#include "pjson/JsonException.hpp"

namespace Json {

	/**
	 * Deserializes a JSON string and returns an instance of Json::Value.
	 * Json::Value provides an easy to use interface to read data.
	 *
	 * A JSON string can be anything which is described in RFC4627.
	 * For example
	 * @code
	 * { "timestamp" : 1319745798, "mood" : "happy" }
	 * @endcode
	 *
	 * @param json The json object as a string.
	 * @throws Json::Exception If the string can not be interpreted as JSON.
	 * @returns A representation of the JSON object.
	 */
	Json::Value
	deserialize(std::string);

	/**
	 * Serializes an object. This will give the json string
	 * representation of any object you give it.
	 * You can give almost any type to this funtion - including
	 * but not limited to:
	 *   - int, float, double
	 *   - std::string
	 *   - map<std::string, T>
	 *   - vector<T>
	 *   - bool
	 *   - const char*
	 *
	 * @param object The object to serialize
	 * @param format How to format the string
	 * @throws Json::Exception if any error is encountered.
	 * @return String representation of the object
	 */
	template <class T> std::string
	serialize(T object, strformat format) throw (Json::Exception)
	{
		Json::Value v = Json::Builder::create(object);
		return v.strjson(format);
	};
}

#endif

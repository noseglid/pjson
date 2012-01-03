#ifndef __PJSON_HPP__
#define __PJSON_HPP__

/** @mainpage
 * @section intro Introduction to pjson
 * The pjson library is intended to be a fast and easy to use JSON
 * interpreter. It turns any valid JSON string into various container types
 * as std:string, int, std::vector and std::map.
 *
 * This library follows the JSON definition in RFC4627.
 *
 * @section quickuse Quick start
 *
 * Here is a quick example to get you started.
 * @include doc-basic.cpp
 * @include doc-basic.out
 *
 * @section structures Using the JSON structures (Array and Object)
 * JSON defines two structure types, Arrays and Objects.
 *
 * @subsection object Object
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
 * @include doc-object.cpp
 * @include doc-object.out
 *
 * @subsection array Array
 * An Array is 0 or more consecutive values enclosed by the delmiters '[' and ']'.
 * @code
 * [ "value1", "value2", 12 ]
 * @endcode
 * These are represented in the pjson library by std::vector<Json::Value*>.
 * Take a look at Json::Array.
 *
 * These can be used just as you would us a normal array
 * @include doc-array.cpp
 * @include doc-array.out
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
	 * A JSON string can be anything which is described in the RFC4627.
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

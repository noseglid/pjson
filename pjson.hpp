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
 * @include basic.cpp
 * @include basic.out
 *
 * @section structures Using the JSON structures (Array and Object)
 * JSON defines two structure types, Arrays and Objects.
 *
 * @subsection array Array
 * An Array is 0 or more consecutive values enclosed by the delmiters '[' and ']'.
 * @code
 * [ "value1", "value2", 12 ]
 * @endcode
 * These are represented in the pjson library by std::vector<Json::Value*>.
 * Take a look at Json::JsonArray.
 *
 * These can be used just as you would us a normal array
 * @include array.cpp
 * @include array.out
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
 * std::map<Json::JsonString, Json::Value*>. Take a look at Json::JsonObject.
 * All normal STL functions for this structures apply
 * @include object.cpp
 * @include object.out
 */

/**
 * @example basic.cpp
 * @example array.cpp
 * @example object.cpp
 */

#include "JsonValue.hpp"
#include "JsonException.hpp"

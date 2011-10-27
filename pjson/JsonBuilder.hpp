#ifndef __JSONBUILDER_HPP__
#define __JSONBUILDER_HPP__

#include "JsonValue.hpp"

#include <map>

namespace Json {

	/// Provides interface for creation of JSON structures.
	/**
	 * Builder is the primary interface for creating and
	 * examining JSON structures.
	 *
	 * The most important functions here are:
	 *  - parse(std::string) Takes any JSON formatted string and
	 *    creates a Json::Value of it.
	 *  - create(Json::value_t) Takes several C++ structures and
	 *    creates a Json::Value of it.
	 *
	 * There are also quite a lot of useful helpers to quickly
	 * create various JSON structures:
	 *  - create(std::map<std::string, T)
	 *  - create(std::vector<T>)
	 */
	class Builder
	{

	private:
		/**
		 * Should never be instansiated.
		 */
		Builder();

	public:

		/**
		 * Parses a JSON string and returns an instance of Json::Value.
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
		static Json::Value parse(std::string json) throw (Json::Exception)
		{
			return Json::Value(json, Json::Value::MODE_PARSE);
		}

		/**
		 * Creates a single value JSON structure.
		 * v can be any of the JSON allowed data structers
		 * represented in C++. These includes;
		 *  - std::string
		 *  - int
		 *  - double
		 *  - bool
		 *  - std::vector<Json::Value*>
		 *  - std::map<std::string, Json::Value*>
		 *
		 * @note These correspond perfectly to what Json::value_t can hold.
		 *
		 * For creating a NULL value, see Json::Builder::create().
		 *
		 * For shorthands to creating structures (avoid having to create all
		 * Json::Value*), see the shorthand functions:
		 *  - Json::Builder::create(std::map<std::string, T>)
		 *  - Json::Builder::create(std::vector<T>)
		 *
		 * @see Json::value_t
		 */
		static Json::Value create(Json::value_t v) throw (Json::Exception)
		{
			return Json::Value(v);
		}

		/**
		 * Creates a NULL valued JSON structure.
		 * To create a JSON structure from any other type,
		 * see Value(Json::value_t).
		 *
		 * @see Value(Json::value_t)
		 */
		static Json::Value create() throw (Json::Exception)
		{
			return Json::Value();
		}

		/**
		 * Creates a JSON Object from std::map.
		 *
		 * The key is always a string in an JSON object,
		 * and the value is templated. The value, however,
		 * must be one of the types in Json::value_t, or castable to one
		 * of these values.
		 *
		 * For example:
		 * @code
		 * std::map<std::string, int> m;
		 * m["fst"] = 0;
		 * m["snd"] = 1;
		 * @endcode
		 *
		 * @tparam T The value of the Object. Must be one of the values
		 *           Json::value_t can hold.
		 * @param v The map which should be interpreted as Json::Value
		 */
		template <class T>
		static Json::Value create(std::map<std::string, T> v) throw (Json::Exception) {
			Json::Object target;

			typedef typename std::map<std::string, T>::const_iterator objit;
			for (objit it = v.begin(); it != v.end(); it++) {
				target[it->first] = new Json::Value(it->second);
			}

			return Json::Value(target);
		}

		/**
		 * Creates a JSON Array from std::vector.
		 *
		 * This is a quick interface to create a JSON Array
		 * and get it represented as Json::Value from the common
		 * C++ structure std::vector.
		 *
		 * For example:
		 * @code
		 * std::vector<std::string> v;
		 * v.push_back(std::string("My first member"));
		 * v.push_back(std::string("My second member"));
		 * @endcode
		 *
		 * @tparam T The value of the Array. Must be one of the values
		 *           Json::value_t can hold.
		 * @param v The vector which should be interpreted as Json::Value
		 */
		template <class T>
		static Json::Value create(std::vector<T> v) throw (Json::Exception) {
			Json::Array target;

			typedef typename std::vector<T>::const_iterator arrit;
			for(arrit it = v.begin(); it != v.end(); it++) {
				target.push_back(new Json::Value(*it));
			}

			return Json::Value(target);
		}
	};

}

#endif

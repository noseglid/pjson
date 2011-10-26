#ifndef __JSONBUILDER_HPP__
#define __JSONBUILDER_HPP__

#include "JsonValue.hpp"

#include <map>

namespace Json {

	class Builder
	{

	private:
		Builder();

	public:

		static Json::Value create(Json::value_t v)
		{
			return Json::Value(v, Json::Value::typeByValue(v));
		}

		static Json::Value create()
		{
			return Json::Value(0, JVNULL);
		}

		template <class T>
		static Json::Value create(std::map<std::string, T> v) {
			Json::Object target;

			typedef typename std::map<std::string, T>::const_iterator objit;
			for (objit it = v.begin(); it != v.end(); it++) {
				target[it->first] = new Json::Value(Json::Builder::create(it->second));
			}

			return Json::Value(target, Json::JVOBJECT);
		}

		template <class T>
		static Json::Value create(std::vector<T> v) {
			Json::Array target;

			typedef typename std::vector<T>::const_iterator arrit;
			for(arrit it = v.begin(); it != v.end(); it++) {
				target.push_back(new Json::Value(Json::Builder::create(*it)));
			}

			return Json::Value(target, Json::JVARRAY);
		}
	};

}

#endif

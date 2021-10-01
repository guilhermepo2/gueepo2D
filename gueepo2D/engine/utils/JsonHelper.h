#pragma once

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include <string>

namespace gueepo::json {
	static bool LoadJSON(const std::string& Filename, rapidjson::Document& OutDocument);

	// #todo
	// I don't really like the fact that I have 4 different functions for this, maybe I could have a Get<T> ?
	// the only issue with that is that I need to reason with the type so I can call Property.IsString(), GetBool(), etc...
	// and also, it gets a little bit more tricky when I get things like Get<Vector2> where the logic changes a little bit
	// #todo create a GetXXX(const rapidjson::Value& InObject, const std::string& InProperty, int& OutXXX); ?
	static bool GetInt		(const rapidjson::Value& InObject, const char* InProperty, int& OutInt);
	static bool GetFloat	(const rapidjson::Value& InObject, const char* InProperty, float& OutFloat);
	static bool GetString	(const rapidjson::Value& InObject, const char* InProperty, std::string& OutString);
	static bool GetBool		(const rapidjson::Value& InObject, const char* InProperty, bool& OutBool);

	// #todo: GetVector2
}

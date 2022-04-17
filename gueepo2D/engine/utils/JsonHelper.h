#pragma once

#pragma warning(push, 0)
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#pragma warning(pop)

namespace gueepo::json {
	static bool LoadJSON(const std::string& Filename, rapidjson::Document& OutDocument);

	static bool GetInt		(const rapidjson::Value& InObject, const char* InProperty, int& OutInt);
	static bool GetFloat	(const rapidjson::Value& InObject, const char* InProperty, float& OutFloat);
	static bool GetString	(const rapidjson::Value& InObject, const char* InProperty, std::string& OutString);
	static bool GetBool		(const rapidjson::Value& InObject, const char* InProperty, bool& OutBool);
	// #todo: GetVector2
	
}

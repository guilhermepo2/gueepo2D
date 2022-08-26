#pragma once
#pragma warning(push, 0)
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#pragma warning(pop)

namespace gueepo {
	static bool JsonHelper_LoadJSON(const std::string& Filename, rapidjson::Document& OutDocument);

	static bool JsonHelper_GetInt		(const rapidjson::Value& InObject, const char* InProperty, int& OutInt);
	static bool JsonHelper_GetFloat	(const rapidjson::Value& InObject, const char* InProperty, float& OutFloat);
	static bool JsonHelper_GetString	(const rapidjson::Value& InObject, const char* InProperty, std::string& OutString);
	static bool JsonHelper_GetBool		(const rapidjson::Value& InObject, const char* InProperty, bool& OutBool);
	// #todo: GetVector2
	
}

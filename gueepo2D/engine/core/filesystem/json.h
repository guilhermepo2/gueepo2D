#pragma once

// ===========================
// json.h
// This is but a wrapper for rapidjson::Document and some helper function
// This should make the class "JsonHelper" useless, but who knows.
// ===========================

#pragma warning(push, 0)
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#pragma warning(pop)

namespace gueepo {

	class json {
	private:
		rapidjson::Document m_json;

		json(const rapidjson::Value& value);
	public:
		json(const std::string& path);

		bool IsValid();
		bool GetInt(const std::string& property, int& outInt);
		bool GetFloat(const std::string& property, float& outFloat);
		bool GetString(const std::string& property, std::string& outString);
		bool GetBool(const std::string& property, bool& outBool);

		bool GetArray(const std::string& property, std::vector<json>& outVec);
	};
}
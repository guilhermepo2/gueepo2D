#pragma once

// ===========================
// json.h
// ===========================

#include <json.hpp>

namespace gueepo {

	class json {
	private:
		nlohmann::json m_json;

	public:
		json(const std::string& path);

		bool IsValid();
		bool GetInt(const std::string& property, int& outInt);
		bool GetFloat(const std::string& property, float& outFloat);
		bool GetString(const std::string& property, std::string& outString);
		bool GetBool(const std::string& property, bool& outBool);
	};
}
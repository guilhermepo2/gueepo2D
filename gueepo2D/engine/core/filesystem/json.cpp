#include "gueepo2Dpch.h"
#include "json.h"
#include "File.h"

namespace gueepo {

	json::json(const std::string& path) {
		File JsonFile(path);
		std::string JsonAsString = JsonFile.GetStringContent();
		m_json.Parse(JsonAsString.c_str());
	}

	bool json::IsValid() {
		return m_json.IsObject();
	}

	bool json::GetInt(const std::string& property, int& outInt) {
		auto itr = m_json.FindMember(property.c_str());

		if (itr == m_json.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsInt()) {
			return false;
		}

		outInt = Property.GetInt();
		return true;
	}

	bool json::GetFloat(const std::string& property, float& outFloat) {
		auto itr = m_json.FindMember(property.c_str());

		if (itr == m_json.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsDouble()) {
			return false;
		}

		outFloat = static_cast<float>(Property.GetDouble());
		return true;
	}

	bool json::GetString(const std::string& property, std::string& outString) {
		auto itr = m_json.FindMember(property.c_str());

		if (itr == m_json.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsString()) {
			return false;
		}

		outString = Property.GetString();
		return true;
	}

	bool json::GetBool(const std::string& property, bool& outBool) {
		auto itr = m_json.FindMember(property.c_str());

		if (itr == m_json.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsBool()) {
			return false;
		}

		outBool = Property.GetBool();
		return true;
	}

}
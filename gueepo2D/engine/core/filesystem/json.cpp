#include "gueepo2Dpch.h"
#include "json.h"
#include "File.h"

namespace gueepo {

    json::json() {}

	json::json(const std::string& path) {
		File JsonFile(path);
		std::string JsonAsString = JsonFile.GetStringContent();
        CreateFromString(JsonAsString);
	}

    void json::CreateFromString(const std::string& jsonContent) {
        m_json = nlohmann::json::parse(jsonContent);
    }

	bool json::IsValid() {
		return m_json.is_object();
	}

	bool json::GetInt(const std::string& property, int& outInt) {
		if(m_json.find(property.c_str()) != m_json.end()) {
			auto element = m_json.at(property.c_str());

			if(element.is_number_integer()) {
				outInt = element.get<int>();
				return true;
			}
		}

		return false;
	}

	bool json::GetFloat(const std::string& property, float& outFloat) {
		if(m_json.find(property.c_str()) != m_json.end()) {
			auto element = m_json.at(property.c_str());

			if(element.is_number_float()) {
				outFloat = element.get<float>();
				return true;
			}
		}

		return false;
	}

	bool json::GetString(const std::string& property, std::string& outString) {
		if(m_json.find(property.c_str()) != m_json.end()) {
			auto element = m_json.at(property.c_str());

			if(element.is_string()) {
				outString = element.get<std::string>();
				return true;
			}
		}

		return false;
	}

	bool json::GetBool(const std::string& property, bool& outBool) {
		if(m_json.find(property.c_str()) != m_json.end()) {
			auto element = m_json.at(property.c_str());

			if(element.is_boolean()) {
				outBool = element.get<bool>();
				return true;
			}
		}

		return false;
	}
}
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


    bool json::GetJsonObject(const std::string &property, json &outJson) {
        if(m_json.find(property.c_str()) != m_json.end()) {
            auto element = m_json.at(property.c_str());
            if(element.is_object()) {
                auto obj = element.get<nlohmann::json>();
                outJson.CreateFromString(obj.dump());
                return true;
            }
        }

        return false;
    }

    // ----------------------------------------------------------------
    // Array Stuff
    // ----------------------------------------------------------------

    bool json::IsArray() {
        return m_json.is_array();
    }

    bool json::GetArray(const std::string &property, json &outJson) {
        if(m_json.find(property.c_str()) != m_json.end()) {
            auto element = m_json.at(property.c_str());

            if(element.is_array()) {
                // #todo: I kind of don't like this, can't I just have a gueepo::json(nlohmann::json)?
                nlohmann::json arrayJsonObject = element.get<nlohmann::json>();
                outJson.CreateFromString(arrayJsonObject.dump());
                return true;
            }
        }

        return false;
    }

    int json::GetArraySize() {
        if(m_json.is_array()) {
            return m_json.size();
        }

        return -1;
    }

    bool json::GetObjectInArray(int index, json &outJson) {
        if(!m_json.is_array()) {
            return false;
        }

        int ArraySize = GetArraySize();
        if(index < 0 || index >= ArraySize) {
            return false;
        }

        nlohmann::json objectAtIndex = m_json[index];
        outJson.CreateFromString(objectAtIndex.dump());
        return true;
    }

    bool json::GetIntAt(int index, int &outInt) {
        if(m_json.is_array() && index >= 0 && index < m_json.size()) {
            nlohmann::json objectAtIndex = m_json[index];
            if(objectAtIndex.is_number()) {
                outInt = objectAtIndex.get<int>();
                return true;
            }
        }

        return false;
    }
}
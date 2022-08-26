#include "gueepo2Dpch.h"
#include "json.h"
#include "File.h"

namespace gueepo {

	json::json(const std::string& path) {
		File JsonFile(path);
		std::string JsonAsString = JsonFile.GetStringContent();
		m_json.Parse(JsonAsString.c_str());
	}

	json::json(const rapidjson::Value& value) {
		m_json.CopyFrom(value, m_json.GetAllocator());
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

	bool json::GetArray(const std::string& property, std::vector<json>& outVec) {
		rapidjson::Value& object = m_json[property.c_str()];
		
		if (object.IsArray()) {
			for (rapidjson::SizeType i = 0; i < object.Size(); i++) {
				outVec.push_back(json(object[i]));
			}

			return true;
		}
		
		return false;
	}

	bool json::GetIntArray(const std::string& property, std::vector<int>& outVec) {
		rapidjson::Value& object = m_json[property.c_str()];

		if (object.IsArray()) {
			for (rapidjson::SizeType i = 0; i < object.Size(); i++) {
				if (object[i].IsInt()) {
					outVec.push_back(object[i].GetInt());
				}
			}
		}

		return false;
	}

}
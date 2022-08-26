#include "gueepo2Dpch.h"
#include "JsonHelper.h"
#include "core/filesystem/File.h"

namespace gueepo {

	// ******************************************************************************************
	bool JsonHelper_LoadJSON(const std::string& Filename, rapidjson::Document& OutDocument) {
		File JsonFile(Filename);
		std::string JsonAsString = JsonFile.GetStringContent();
		OutDocument.Parse(JsonAsString.c_str());
		return OutDocument.IsObject();
	}

	// ******************************************************************************************
	bool JsonHelper_GetInt(const rapidjson::Value& InObject, const char* InProperty, int& OutInt) {
		auto itr = InObject.FindMember(InProperty);

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsInt()) {
			return false;
		}

		OutInt = Property.GetInt();
		return true;
	}

	// ******************************************************************************************
	bool JsonHelper_GetFloat(const rapidjson::Value& InObject, const char* InProperty, float& OutFloat) {
		auto itr = InObject.FindMember(InProperty);

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsDouble()) {
			return false;
		}

		OutFloat = static_cast<float>(Property.GetDouble());
		return true;
	}

	// ******************************************************************************************
	bool JsonHelper_GetString(const rapidjson::Value& InObject, const char* InProperty, std::string& OutString) {
		auto itr = InObject.FindMember(InProperty);

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsString()) {
			return false;
		}

		OutString = Property.GetString();
		return true;
	}

	// ******************************************************************************************
	bool JsonHelper_GetBool(const rapidjson::Value& InObject, const char* InProperty, bool& OutBool) {
		auto itr = InObject.FindMember(InProperty);

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsBool()) {
			return false;
		}

		OutBool = Property.GetBool();
		return true;
	}

}
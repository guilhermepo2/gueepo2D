#include "JsonHelper.h"
#include "core/filesystem/File.h"

namespace gueepo::json {

	// ******************************************************************************************
	bool LoadJSON(const std::string& Filename, rapidjson::Document& OutDocument) {
		File JsonFile(Filename);
		std::string JsonAsString = JsonFile.GetStringContent();
		OutDocument.Parse(JsonAsString.c_str());
		return OutDocument.IsObject();
	}

	// ******************************************************************************************
	bool GetInt(const rapidjson::Value& InObject, const char* InProperty, int& OutInt) {
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
	bool GetFloat(const rapidjson::Value& InObject, const char* InProperty, float& OutFloat) {
		auto itr = InObject.FindMember(InProperty);

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsDouble()) {
			return false;
		}

		OutFloat = Property.GetDouble();
		return true;
	}

	// ******************************************************************************************
	bool GetString(const rapidjson::Value& InObject, const char* InProperty, std::string& OutString) {
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
	bool GetBool(const rapidjson::Value& InObject, const char* InProperty, bool& OutBool) {
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
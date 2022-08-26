#pragma once
#include "core/filesystem/json.h"

TEST_CASE("json test", "[filesystem]") {
	gueepo::json testJson("./assets/test.json");
	bool outBool;
	int outInt;
	float outFloat;
	std::string outString;

	REQUIRE(testJson.IsValid() == true);
	
	testJson.GetBool("boolean", outBool);
	testJson.GetInt("number", outInt);
	testJson.GetFloat("floating", outFloat);
	testJson.GetString("color", outString);

	REQUIRE(outBool == true);
	REQUIRE(outInt == 123);
	REQUIRE(outFloat == 3.5);
	REQUIRE(outString == "gold");
}

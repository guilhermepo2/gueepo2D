#pragma once
#include "core/filesystem/json.h"

const char* testJsonString =
        "{\n"
        "\"bval\": true,\n"
        "\"color\": \"gold\",\n"
        "\"number\": 123,\n"
        "\"floating\": 3.5\n"
        "}\n";

TEST_CASE("json test", "[filesystem]") {
	gueepo::json testJson;
    testJson.CreateFromString(testJsonString);

	bool outBool;
	int outInt;
	float outFloat;
	std::string outString;

	REQUIRE(testJson.IsValid() == true);
	
	REQUIRE(testJson.GetBool("bval", outBool));
    REQUIRE(testJson.GetInt("number", outInt));
    REQUIRE(testJson.GetFloat("floating", outFloat));
    REQUIRE(testJson.GetString("color", outString));

	REQUIRE( outBool == true );
	REQUIRE(outInt == 123);
	REQUIRE(outFloat == 3.5);
	REQUIRE(outString == "gold");
}

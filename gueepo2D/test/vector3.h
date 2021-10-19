#pragma once
#include "thirdparty/catch.hpp"
#include "core/math/Vector3.h"

TEST_CASE("VECTOR3", "[math]") {
	SECTION("empty constructor") {
		gueepo::math::Vector3 v;
		REQUIRE(v.x == 0.0f);
		REQUIRE(v.y == 0.0f);
		REQUIRE(v.z == 0.0f);
	}

	SECTION("single parameter constructor") {
		gueepo::math::Vector3 v(1.0f);
		REQUIRE(v.x == 1.0f);
		REQUIRE(v.y == 1.0f);
		REQUIRE(v.z == 1.0f);
	}

	SECTION("three parameter constructor") {
		gueepo::math::Vector3 v(2.0f, 4.0f, 6.0f);
		REQUIRE(v.x == 2.0f);
		REQUIRE(v.y == 4.0f);
		REQUIRE(v.z == 6.0f);
	}

	SECTION("copy constructor") {
		gueepo::math::Vector3 base(3.0f, 6.0f, 9.0f);
		gueepo::math::Vector3 v(base);
		REQUIRE(v.x == 3.0f);
		REQUIRE(v.y == 6.0f);
		REQUIRE(v.z == 9.0f);
	}
}


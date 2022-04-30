#pragma once
#include "core/math/Vector2.h"
#include "TestUtils.h"

TEST_CASE("VECTOR2", "[math]") {

	SECTION("empty constructor") {
		gueepo::math::Vector2 v;
		REQUIRE(v.x == 0.0f);
		REQUIRE(v.y == 0.0f);
	}

	SECTION("single parameter constructor") {
		gueepo::math::Vector2 v(1.0f);
		REQUIRE(v.x == 1.0f);
		REQUIRE(v.y == 1.0f);
	}

	SECTION("two parameter constructor") {
		gueepo::math::Vector2 v(2.0f, 4.0f);
		REQUIRE(v.x == 2.0f);
		REQUIRE(v.y == 4.0f);
	}

	SECTION("copy constructor") {
		gueepo::math::Vector2 base(3.0f, 6.0f);
		gueepo::math::Vector2 v(base);
		REQUIRE(v.x == 3.0f);
		REQUIRE(v.y == 6.0f);
	}

	SECTION("vector2 + vector2") {
		gueepo::math::Vector2 a(3.0f, 5.0f);
		gueepo::math::Vector2 b(1.0f, 2.0f);
		gueepo::math::Vector2 sum = a + b;

		REQUIRE(sum.x == 4.0f);
		REQUIRE(sum.y == 7.0f);
	}

	SECTION("vector2 - vector2") {
		gueepo::math::Vector2 a(3.0f, 5.0f);
		gueepo::math::Vector2 b(1.0f, 2.0f);
		gueepo::math::Vector2 result = a - b;

		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 3.0f);
	}

	SECTION("vector2 * float") {
		gueepo::math::Vector2 a(3.0f, 5.0f);
		gueepo::math::Vector2 result = a * 2.0f;

		REQUIRE(result.x == 6.0f);
		REQUIRE(result.y == 10.0f);
	}

	SECTION("float * vector2") {
		gueepo::math::Vector2 a(3.0f, 5.0f);
		gueepo::math::Vector2 result = 2.0f * a;

		REQUIRE(result.x == 6.0f);
		REQUIRE(result.y == 10.0f);
	}

	SECTION("vector2 == vector2") {
		gueepo::math::Vector2 a(3.0f, 5.0f);
		gueepo::math::Vector2 b(3.0f, 5.0f);

		REQUIRE(a == b);
	}

	SECTION("vector2 != vector2") {
		gueepo::math::Vector2 a(3.0f, 5.0f);
		gueepo::math::Vector2 b(2.0f, 4.0f);

		REQUIRE(a != b);
	}

	SECTION("magnitude / normalization") {
		// unit vectors
		gueepo::math::Vector2 UnitX(1.0f, 0.0f);
		gueepo::math::Vector2 UnitY(0.0f, 1.0f);
		gueepo::math::Vector2 UnitZ(0.0f, 0.0f);
		REQUIRE(UnitX.GetLength() == 1.0f);
		REQUIRE(UnitY.GetLength() == 1.0f);
		REQUIRE(UnitZ.GetLength() == 0.0f);

		// testing normalization
		gueepo::math::Vector2 p(3.0f, 4.0f);
		gueepo::math::Vector2 q(11.0f, 7.0f);
		REQUIRE(p.GetNormalized().GetLength() == 1.0f);
		REQUIRE(q.GetNormalized().GetLength() == 1.0f);
	}
}
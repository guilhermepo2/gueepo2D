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

	SECTION("vector3 operator+ overloading") {
		gueepo::math::Vector3 a(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 b(2.0f, 3.0f, 4.0f);
		gueepo::math::Vector3 sum = a + b;

		REQUIRE(sum.x == 3.0f);
		REQUIRE(sum.y == 5.0f);
		REQUIRE(sum.z == 7.0f);
	}

	SECTION("vector3 operator- overloading") {
		gueepo::math::Vector3 a(5.0f, 5.0f, 5.0f);
		gueepo::math::Vector3 b(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 result = a - b;

		REQUIRE(result.x == 4.0f);
		REQUIRE(result.y == 3.0f);
		REQUIRE(result.z == 2.0f);
	}

	SECTION("vector3 scalar multiplication") {
		gueepo::math::Vector3 a(2.0f, 3.0f, 4.0f);
		float scalar = 3.0f;
		gueepo::math::Vector3 result = a * scalar;
		
		REQUIRE(result.x == 6.0f);
		REQUIRE(result.y == 9.0f);
		REQUIRE(result.z == 12.0f);
	}

	SECTION("vector3 scalar multiplication") {
		gueepo::math::Vector3 a(2.0f, 3.0f, 4.0f);
		float scalar = 3.0f;
		gueepo::math::Vector3 result = a * scalar;

		REQUIRE(result.x == 6.0f);
		REQUIRE(result.y == 9.0f);
		REQUIRE(result.z == 12.0f);
	}

	SECTION("vector3 == and != operators") {
		gueepo::math::Vector3 a(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 a2(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 b(2.0f, 4.0f, 6.0f);

		REQUIRE(a == a2);
		REQUIRE(a != b);
	}

	SECTION("theorem 2.1") {
		// given any two scalars a and b,
		float a = 0.37f;
		float b = 1.33f;
		// and any three vectors, P, Q, and R
		gueepo::math::Vector3 p(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 q(2.0f, 1.5f, 4.5f);
		gueepo::math::Vector3 r(3.0f, 4.0f, 9.0f);
		// the following properties hold

		// (a)
		REQUIRE((p + q) == (q + p));
		// (b)
		REQUIRE( ((p+q)+r) == (p+(q+r)) );
		// (c)
		REQUIRE( ((a*b)*p) == (a*(b*p)) );
		// (d)
		REQUIRE( (a*(p+q)) == (a*p + a*q) );
		// (e)
		REQUIRE( ((a + b) * p) == (a*p + b*p) );
	}

	SECTION("magnitude and normalization") {
		// unit vectors
		gueepo::math::Vector3 UnitX(1.0f, 0.0f, 0.0f);
		gueepo::math::Vector3 UnitY(0.0f, 1.0f, 0.0f);
		gueepo::math::Vector3 UnitZ(0.0f, 0.0f, 1.0f);
		REQUIRE(UnitX.GetLength() == 1.0f);
		REQUIRE(UnitY.GetLength() == 1.0f);
		REQUIRE(UnitZ.GetLength() == 1.0f);

		// testing magnitude
		gueepo::math::Vector3 a(2.0f, 3.0f, 4.0f);
		gueepo::math::Vector3 b(1.0f, 1.0f, 1.0f);
		REQUIRE(a.GetLength() == Approx(5.38516f));
		REQUIRE(b.GetLength() == Approx(1.73205f));

		// testing normalization
		gueepo::math::Vector3 p(3.0f, 4.0f, 5.0f);
		gueepo::math::Vector3 q(11.0f, 7.0f, -1.0f);
		REQUIRE(p.GetNormalized().GetLength() == 1.0f);
		REQUIRE(q.GetNormalized().GetLength() == 1.0f);
	}

	SECTION("theorem 2.2") {
		// given any scalar a
		float a = 1.73f;
		// and any two vectors p and q
		gueepo::math::Vector3 p(8.98326f, 5.65836f, 5.54062f);
		gueepo::math::Vector3 q(1.41782f, 2.42726f, 0.41432f);
		gueepo::math::Vector3 z(0.0f, 0.0f, 0.0f);

		// (a)
		REQUIRE(p.GetLength() >= 0.0f);
		REQUIRE(q.GetLength() >= 0.0f);
		// (b)
		REQUIRE(z.GetLength() == 0.0f);
		// (c)
		REQUIRE( ( (a*p).GetLength() ) == Approx( (abs(a) * p.GetLength() ) ) );
		REQUIRE( ( (a*q).GetLength() ) == Approx( (abs(a) * q.GetLength() ) ) );
		// (d)
		REQUIRE( ( (p+q).GetLength() ) <= ( p.GetLength() + q.GetLength() ) );
	}
}


#pragma once
#include "thirdparty/catch.hpp"
#include "core/math/Vector3.h"
#include "TestUtils.h"

TEST_CASE("VECTOR3", "[math]") {
	
	gueepo::test::ResetRandomSeed();

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
		gueepo::math::Vector3 result2 = a * 2;
		
		REQUIRE(result2.x == 4.0f);
		REQUIRE(result2.y == 6.0f);
		REQUIRE(result2.z == 8.0f);

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
		float a = static_cast<float>(gueepo::test::RandomInt(0, 10));
		float b = static_cast<float>(gueepo::test::RandomInt(0, 10));
		INFO("a: " << a);
		INFO("b: " << b);
		// and any three vectors, P, Q, and R
		gueepo::math::Vector3 p = gueepo::test::RandomVector();
		gueepo::math::Vector3 q = gueepo::test::RandomVector();
		gueepo::math::Vector3 r = gueepo::test::RandomVector();
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
		float a = static_cast<float>(gueepo::test::RandomInt(0, 10));
		// and any two vectors p and q
		gueepo::math::Vector3 p = gueepo::test::RandomVector();
		gueepo::math::Vector3 q = gueepo::test::RandomVector();
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

	SECTION("dot product") {
		gueepo::math::Vector3 v1(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 v2(5.0f, 6.f, 7.0f);

		float dotproduct = gueepo::math::Vector3::Dot(v1, v2);
		REQUIRE(dotproduct == Approx(38.0f));

		gueepo::math::Vector3 v3(1.0f, -1.0f, 1.0f);
		gueepo::math::Vector3 v4(-2.0f, 2.0f, 2.0f);
		float dotproduct2 = gueepo::math::Vector3::Dot(v3, v4);
		REQUIRE(dotproduct2 == -2.0f);
	}

	SECTION("theorem 2.5") {
		gueepo::math::Vector3 p = gueepo::test::RandomVector();
		gueepo::math::Vector3 q = gueepo::test::RandomVector();
		gueepo::math::Vector3 r = gueepo::test::RandomVector();
		float scalar = static_cast<float>(gueepo::test::RandomInt());


		// (a)
		REQUIRE(gueepo::math::Vector3::Dot(p, q) == gueepo::math::Vector3::Dot(q, p));
		// (b)
		REQUIRE(gueepo::math::Vector3::Dot((scalar * p), q) == Approx(scalar * gueepo::math::Vector3::Dot(p, q)));
		// (c)
		REQUIRE(
			gueepo::math::Vector3::Dot(p, (q + r)) ==
			Approx(gueepo::math::Vector3::Dot(p, q) + gueepo::math::Vector3::Dot(p, r))
		);
		// (d)
		REQUIRE(
			gueepo::math::Vector3::Dot(p, p) ==
			Approx(p.GetLength() * p.GetLength())
		);
		// (e)
		REQUIRE(
			abs(gueepo::math::Vector3::Dot(p, q)) <=
			p.GetLength() * q.GetLength()
		);

	}

	SECTION("cross product") {
		gueepo::math::Vector3 a(2.0f, 3.0f, 4.0f);
		gueepo::math::Vector3 b(1.0f, 1.0f, 2.0f);
		gueepo::math::Vector3 cross = gueepo::math::Vector3::Cross(a, b);

		REQUIRE(cross.x == 2.0f);
		REQUIRE(cross.y == 0.0f);
		REQUIRE(cross.z == -1.0f);

		gueepo::math::Vector3 c(3.0f, 2.0f, 1.0f);
		gueepo::math::Vector3 d(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 cross2 = gueepo::math::Vector3::Cross(c, d);

		REQUIRE(cross2.x == 4.0f);
		REQUIRE(cross2.y == -8.0f);
		REQUIRE(cross2.z == 4.0f);
	}

	SECTION("theorem 2.7") {
		gueepo::math::Vector3 p(3.0f, 2.0f, 1.0f);
		gueepo::math::Vector3 q(1.0f, 2.0f, 3.0f);

		REQUIRE(gueepo::math::Vector3::Dot((gueepo::math::Vector3::Cross(p, q)), p) == 0);
		REQUIRE(gueepo::math::Vector3::Dot((gueepo::math::Vector3::Cross(p, q)), q) == 0);
	}

	SECTION("theorem 2.9") {
		gueepo::math::Vector3 p(3.0f, 2.0f, 1.0f);
		gueepo::math::Vector3 q(1.0f, 2.0f, 3.0f);
		gueepo::math::Vector3 r(2.0f, 1.0f, 1.0f);
		float a = static_cast<float>(gueepo::test::RandomInt(1, 5));

		// (a)
		REQUIRE(
			gueepo::math::Vector3::Cross(q, p) ==
			( -1 * gueepo::math::Vector3::Cross(p,q))
		);
		// (b)
		REQUIRE(
			gueepo::math::Vector3::Cross(a*p, q) ==
			(a * gueepo::math::Vector3::Cross(p, q))
		);
		// (c)
		REQUIRE(
			gueepo::math::Vector3::Cross(p, (q + r)) ==
			gueepo::math::Vector3::Cross(p, q) + gueepo::math::Vector3::Cross(p, r)
		);
		// (d)
		REQUIRE(
			gueepo::math::Vector3::Cross(p, p) == gueepo::math::Vector3(0.0f)
		);
		// (e)
		REQUIRE(
			gueepo::math::Vector3::Dot(gueepo::math::Vector3::Cross(p,q), r) ==
			gueepo::math::Vector3::Dot(gueepo::math::Vector3::Cross(r, p), q)
		);
		REQUIRE(
			gueepo::math::Vector3::Dot(gueepo::math::Vector3::Cross(p, q), r) ==
			gueepo::math::Vector3::Dot(gueepo::math::Vector3::Cross(q, r), p)
		);
		REQUIRE(
			gueepo::math::Vector3::Dot(gueepo::math::Vector3::Cross(r, p), q) ==
			gueepo::math::Vector3::Dot(gueepo::math::Vector3::Cross(q, r), p)
		);
		// (f)
		REQUIRE(
			gueepo::math::Vector3::Cross(p, gueepo::math::Vector3::Cross(q, p)) == 
			gueepo::math::Vector3::Cross(gueepo::math::Vector3::Cross(p, q), p)
		);
		
	}
}


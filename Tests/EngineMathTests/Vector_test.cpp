//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "math/Vector.h"

using namespace math;

namespace math_tests {

	TEST(Vector2Tests, MultiplicationTest) {
		//Vector 2
		Vector2 v1(1, 2);
		auto v2 = v1 * 2;

		ASSERT_EQ(Vector2(2, 4), v2);

		v2 *= 4;
		ASSERT_EQ(Vector2(8, 16), v2);
	}

	TEST(Vector2Tests, DivisionTest) {
		Vector2 v1(1, 2);
		auto v2 = v1 / 2;

		ASSERT_EQ(Vector2(0.5f, 1.0f), v2);

		v2 /= 2;
		ASSERT_EQ(Vector2(0.25, 0.5), v2);
	}

	TEST(Vector2Tests, AdditionTest) {
		Vector2 v1(1, 2);
		Vector2 v2(v1);
		auto v3 = v1 + v2;

		ASSERT_EQ(Vector2(2, 4), v3);

		v3 += Vector2(1, 1);
		ASSERT_EQ(Vector2(3, 5), v3);
	}

	TEST(Vector3Tests, MultiplicationTest) {
		Vector3 v1(1, 2, 3);
		auto v2 = v1 * 2;

		ASSERT_EQ(Vector3(2, 4, 6), v2);

		v2 *= 4;
		ASSERT_EQ(Vector3(8, 16, 24), v2);
	}

	TEST(Vector3Tests, DivisionTest) {
		Vector3 v1(1, 2, 3);
		auto v2 = v1 / 2;

		ASSERT_EQ(Vector3(0.5f, 1.0f, 1.5f), v2);

		v2 /= 2;
		ASSERT_EQ(Vector3(0.25, 0.5, 0.75f), v2);
	}

	TEST(Vector3Tests, AdditionTest) {
		Vector3 v1(1, 2, 3);
		Vector3 v2(v1);
		auto v3 = v1 + v2;

		ASSERT_EQ(Vector3(2, 4, 6), v3);

		v3 += Vector3(1, 1, 1);
		ASSERT_EQ(Vector3(3, 5, 7), v3);
	}

	TEST(Vector3Tests, ConstructionTest) {
		Vector3 v1(1, 2, 3);
		ASSERT_EQ(1, v1.X);
		ASSERT_EQ(2, v1.Y);
		ASSERT_EQ(3, v1.Z);

		Vector3 v2(Vector2(5, 5));
		ASSERT_EQ(5, v2.X);
		ASSERT_EQ(5, v2.Y);
		ASSERT_EQ(0, v2.Z);

		Vector3 v3(Vector2(5, 5), 5);
		ASSERT_EQ(5, v3.X);
		ASSERT_EQ(5, v3.Y);
		ASSERT_EQ(5, v3.Z);
	}

};
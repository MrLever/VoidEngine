//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "math/Rotator.h"
#include "math/Quaternion.h"

using namespace math;

namespace math_tests {

	TEST(RotatorTests, Equivalence) {
		Rotator r1(0, 0, 0);
		Rotator r2(90, 0, 0);
		Rotator r3(450, 0, 0);
		ASSERT_NE(r1, r2);
		ASSERT_EQ(r2, r3);
	}

	TEST(RotatorTests, ToVector) {
		Rotator rot(0, 90, 0);
		Quaternion quat(rot);

		auto f1 = rot.AsVector();
		auto f2 = quat.AsVector();
		
		ASSERT_EQ(f1, f2);
	}

	TEST(RotatorTests, Normalize) {
		Rotator r1(0, 340, 0);
		Rotator r2(0, 700, 0);
		Rotator r3(0, -20, 0);
		r2.Normalize();
		r3.Normalize();

		ASSERT_EQ(r1, r2);
		ASSERT_EQ(r1, r3);
	}

};
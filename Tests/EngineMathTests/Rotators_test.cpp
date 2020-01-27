//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "EngineMath/Rotator.h"
#include "EngineMath/Quaternion.h"

using namespace math;

namespace math_tests {

	TEST(RotatorTests, Equivalence) {
		Rotator r1(0, 0, 0);
		Rotator r2(.5f, .5f, .5f);
		Rotator r3(.5f, .5f, .5f);
		ASSERT_NE(r1, r2);
		ASSERT_EQ(r2, r3);
	}

	TEST(RotatorTests, ToVector) {
		Rotator rot(0, 90, 0);
		Quaternion quat(rot);

		auto f1 = rot.ToVector();
		auto f2 = quat.ToVector();
		
		ASSERT_EQ(f1, f2);
	}
};
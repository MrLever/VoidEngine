//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "math/Quaternion.h"
#include "math/Rotator.h"
#include "math/Vector.h"


using namespace math;

namespace math_tests {

	TEST(QuaternionTests, EulerConversion){
		Rotator expected(0, -90, 0);
		Quaternion quat(expected);
		ASSERT_TRUE(quat == math::Quaternion(.7071068f, 0, -.7071068f, 0));

		auto result = quat.ToEuler();

		ASSERT_TRUE(expected.Equals(result, 0.02f));
	}

	TEST(QuaternionTests, VectorRotation){
		//Test X-Y Plane Rotations
		Vector3 test(1, 0, 0);
		Rotator rotation(0, 0, 45);
		Quaternion quat(rotation);
		auto result = quat.Rotate(test);
		ASSERT_TRUE(
			result == Vector3(std::cosf(ToRadians(45)), std::sinf(ToRadians(45)), 0)
		);

		//Test Y-Z Plane Rotations
		test = Vector3(0, 1, 0);
		rotation = Rotator(60, 0, 0);
		quat = Quaternion(rotation);
		result = quat.Rotate(test);
		ASSERT_TRUE(
			result == Vector3(0, std::cosf(ToRadians(60)), std::sinf(ToRadians(60)))
		);

		//Test X-Z Plane Rotations
		test = Vector3(1, 0, 0);
		rotation = Rotator(0, 90, 0);
		quat = Quaternion(rotation);
		result = quat.Rotate(test);
		ASSERT_TRUE(
			result == Vector3(0,0,-1)
		);
	}

	TEST(QuaternionTests, ToVector){
		Rotator rotation(0, 90, 0);
		Quaternion quat(rotation);
		Vector3 expected(0, 0, -1);
		auto actual = quat.ToVector();

		ASSERT_EQ(expected, actual);
	}

	TEST(QuaternionTests, CompositionTest){
		Quaternion q1(Rotator(0, -45, 0));
		Quaternion q2(Rotator(0, 10, 0));
	
		auto result = (q1 * q2).ToEuler();
		ASSERT_TRUE(Rotator(0, -35, 0) == result);
	}

}
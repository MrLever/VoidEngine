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
		Rotator OneDegreeEuler(0, 1, 0);
		Quaternion OneDegreeQuat(OneDegreeEuler);
		Quaternion curr = Quaternion::Identity;

		for (int i = 0; i <= 360; i++) {
			ASSERT_EQ(Quaternion(Rotator(0, (float)i, 0)), curr);
			curr *= OneDegreeQuat;
		}

	}

	TEST(QuaternionTests, InverseTest) {
		Rotator expected(0, -90, 0);
		Rotator init(0, 90, 0);

		Quaternion quat(init);
		ASSERT_TRUE(quat == math::Quaternion(.7071068f, 0, -.7071068f, 0));

		//Proof of identity property
		Quaternion quatPrime = quat.Inverse();
		auto identity = quat * quatPrime;
		ASSERT_TRUE(identity == math::Quaternion(1, 0, 0, 0));

		//Left rotation
		auto result = quat * quatPrime;
		auto distance = Quaternion(math::Rotator(0, 0, 0)).Dot(result);
		ASSERT_EQ(0.0f, std::acosf(distance));

		//Another left rotation
		auto result2 = result * quatPrime;
		distance = Quaternion(math::Rotator(0, -90, 0)).Dot(result2);
		ASSERT_EQ(0.0f, std::acosf(distance));
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
		auto actual = quat.AsVector();

		ASSERT_EQ(expected, actual);
	}

	TEST(QuaternionTests, CompositionTest){
		Quaternion q1(Rotator(0, -45, 0));
		Quaternion q2(Rotator(0, 10, 0));
	
		auto result = (q1 * q2).AsEuler();
		ASSERT_TRUE(Rotator(0, -35, 0) == result);
	}

}
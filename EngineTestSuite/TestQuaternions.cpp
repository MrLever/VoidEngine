//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Quaternion.h"
#include "Rotator.h"
#include "Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace math;

namespace EngineMathTests {

	TEST_CLASS(QuaternionTests) {
	public:
		TEST_METHOD(EulerConversionTests) {
			for (int i = 0; i < 180; i++) {
				for (int j = 0; j < 180; j++) {
					for (int k = 0; k < 180; k++) {
						Rotator r1(50, 50, 50);
						Quaternion q(r1);
						Assert::IsTrue(q.IsValid());
						Rotator r2 = q.ToEuler();
						Assert::IsTrue(q.ToEuler() == r1);
					}
				}
			}
		}

		TEST_METHOD(VectorRotationTests) {
			//Test X-Y Plane Rotations
			Vector3 test(1, 0, 0);
			Rotator rotation(0, 0, 45);
			Quaternion quat(rotation);
			auto result = quat.Rotate(test);
			Assert::IsTrue(
				result == Vector3(std::cosf(ToRadians(45)), std::sinf(ToRadians(45)), 0)
			);
		
			//Test Y-Z Plane Rotations
			test = Vector3(0, 1, 0);
			rotation = Rotator(60, 0, 0);
			quat = Quaternion(rotation);
			result = quat.Rotate(test);
			Assert::IsTrue(
				result == Vector3(0, std::cosf(ToRadians(60)), std::sinf(ToRadians(60)))
			);

			//Test X-Z Plane Rotations
			test = Vector3(0, 0, 1);
			rotation = Rotator(0, 60, 0);
			quat = Quaternion(rotation);
			result = quat.Rotate(test);
			Assert::IsTrue(
				result == Vector3(std::sinf(ToRadians(60)), 0, std::cosf(ToRadians(60)))
			);

		}

		TEST_METHOD(QuaternionCompositionTest) {
			Quaternion q1(Rotator(0, -45, 0));
			Quaternion q2(Rotator(0, 10, 0));

			auto result = (q1 * q2).ToEuler();

			Assert::IsTrue(Rotator(0, -35, 0) == result);
		}

	};
};
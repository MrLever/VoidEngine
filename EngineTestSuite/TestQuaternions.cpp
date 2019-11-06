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
			Vector3 test(1, 0, 0);
			Rotator rotation(0, 0, 60);

			Quaternion quat(rotation);

			auto result = quat.Rotate(test);

			Assert::IsTrue(result == Vector3(.5,0,0));
		}

	};
};
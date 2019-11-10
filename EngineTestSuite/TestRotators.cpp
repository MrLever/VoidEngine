//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Rotator.h"
#include "Quaternion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace math;

namespace EngineMathTests {

	TEST_CLASS(RotatorTests) {
	public:
		TEST_METHOD(RotatorEquivalenceTests) {
			Rotator r1(0, 0, 0);
			Rotator r2(.5f, .5f, .5f);
			Assert::IsFalse(r1 == r2);
			Assert::IsTrue(r2 == r2);
		}
		
		TEST_METHOD(RotatorToVectorTests) {
			Rotator rot(0, 90, 0);
			Quaternion quat(rot);

			auto f1 = rot.ToVector();
			auto f2 = quat.ToVector();

			Assert::IsTrue(f1 == f2);
		}
	};
};
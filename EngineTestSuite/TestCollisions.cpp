//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Quaternion.h"
#include "Rotator.h"
#include "Vector.h"
#include "Collider.h"
#include "Entity.h"
#include "ColliderComponent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace core;

namespace EngineCoreTests {

	class DummyRigidBody : public Entity {
	public: 
		void BeginPlay() {}
		void Terminate() {}

		ColliderComponent* collider;
	};

	TEST_CLASS(CollisionTests) {
	public:
		TEST_METHOD(SphereToSphereColliderTest) {
			DummyRigidBody r1;
			DummyRigidBody r2;

			r1.collider = new ColliderComponent();
			nlohmann::json data;
			/*r1.collider->SetComponentData();
			r1.collider->SetComponentData();*/

			Assert::Fail();
		}
	};
};
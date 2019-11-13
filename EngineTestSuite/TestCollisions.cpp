//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Quaternion.h"
#include "Rotator.h"
#include "Vector.h"
#include "Entity.h"
#include "SphereCollider.h"

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

			r1.collider = new SphereCollider();
			r2.collider = new SphereCollider();

			r1.SetPosition(math::Vector3(0, 0, 0));
			r2.SetPosition(math::Vector3(0, 2, 0));

			Assert::IsFalse(r1.collider->DetectCollision(r2.collider));

			//nlohmann::json data;
			/*r1.collider->SetComponentData();
			r1.collider->SetComponentData();*/
		}
	};
};
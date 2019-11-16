//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Quaternion.h"
#include "Rotator.h"
#include "Vector.h"
#include "Entity.h"
#include "ColliderComponent.h"
#include "SphereCollider.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace core;

namespace EngineCoreTests {

	class DummyRigidBody : public Entity {
	public: 
		void BeginPlay() {}
		void Terminate() {}
	};

	TEST_CLASS(CollisionTests) {
	public:
		TEST_METHOD(SphereSphereCollisionTest) {
			DummyRigidBody r1;
			DummyRigidBody r2;

			ColliderComponent* c1 = new ColliderComponent();
			ColliderComponent* c2 = new ColliderComponent();

			r1.AddComponent(c1);
			r2.AddComponent(c2);

			r1.SetPosition(math::Vector3(0, 0, 0));
			r2.SetPosition(math::Vector3(0, 1, 0));

			r1.Initialize();
			r2.Initialize();

			Assert::IsTrue(false);
		}
	};
};
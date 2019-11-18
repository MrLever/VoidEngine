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
#include "ResourceAllocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace core;

namespace EngineCoreTests {
	/** macro is required here because of .dll boundary in test suite */
	ENABLE_FACTORY(SphereCollider, Collider)

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
			
			EntityData data("Resources/Testing/Entities/CollisionTestEntity.json");
			data.Load();
			auto componentData = data.GetAttribute<nlohmann::json>("components");
			auto colliderComponentData = componentData[1];

			ColliderComponent* c1 = new ColliderComponent();
			c1->SetConfigData(colliderComponentData);
			r1.AddComponent(c1);

			ColliderComponent* c2 = new ColliderComponent();
			c2->SetConfigData(colliderComponentData);
			r2.AddComponent(c2);

			r1.Initialize();
			r1.SetPosition(math::Vector3(0, 0, 0));
			r2.Initialize();
			r2.SetPosition(math::Vector3(0, 1, 0));
			r1.Tick(.5f);
			r2.Tick(.5f);
			
			Assert::IsTrue(c1->DetectCollision(c2));

			r2.SetPosition(math::Vector3(0, 2, 0));
			r2.Tick(.5f);
			Assert::IsTrue(c1->DetectCollision(c2));

			r2.SetPosition(math::Vector3(0, 2.1f, 0));
			r2.Tick(.5f);
			Assert::IsFalse(c1->DetectCollision(c2));

		}
	};
};
//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/gameplay_framework/Entity.h"
#include "core/physics/colliders/AABBCollider.h"
#include "core/physics/colliders/SphereCollider.h"
#include "core/physics/components/ColliderComponent.h"

#include "math/Quaternion.h"
#include "math/Rotator.h"
#include "math/Vector.h"
#include "utils/resource/ResourceAllocator.h"

using namespace core;

namespace EngineCoreTests {
	/** macro is required here because of .dll boundary in test suite */
	ENABLE_FACTORY(SphereCollider, Collider)
	ENABLE_FACTORY(AABBCollider, Collider)

	class DummyRigidBody : public Entity {
	public: 
		void BeginPlay() {}
		void Terminate() {}
	};

	TEST(ColliderComponentTests, SphereSphereCollisionTest) {
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
			
		Manifold* manifold = c1->DetectCollision(c2);
			
		ASSERT_EQ(1.0f, manifold->PenetrationDistance);
		delete manifold;

		r2.SetPosition(math::Vector3(0, 2, 0));
		r2.Tick(.5f);
		manifold = c1->DetectCollision(c2);
		ASSERT_NE(nullptr, manifold);
		ASSERT_EQ(0.0f, manifold->PenetrationDistance);
		delete manifold;

		r2.SetPosition(math::Vector3(0, 2.01f, 0));
		r2.Tick(.5f);
		manifold = c1->DetectCollision(c2);
		ASSERT_EQ(nullptr, manifold);

		r2.SetPosition(math::Vector3(0, -1.0f, 0));
		r2.Tick(.5f);
		manifold = c1->DetectCollision(c2);
		ASSERT_EQ(1.0f, manifold->PenetrationDistance);
		delete manifold;
	}

	TEST(ColliderComponentTests, AABB_AABB_CollisionTest) {
		DummyRigidBody r1;
		DummyRigidBody r2;
		Manifold* manifold = nullptr;

		nlohmann::json colliderData = {
				{"type", "ColliderComponent"},
				{
					"shape",
					{
						{"type", "AABBCollider"},
						{"min", {-0.5f, -0.5f, -0.5f}},
						{"max", {0.5f, 0.5f, 0.5f}}
					}
				}
		};

		ColliderComponent* c1 = new ColliderComponent();
		c1->SetConfigData(colliderData);
		r1.AddComponent(c1);

		ColliderComponent* c2 = new ColliderComponent();
		c2->SetConfigData(colliderData);
		r2.AddComponent(c2);

		//Test Y axis
		r1.Initialize();
		r1.SetPosition(math::Vector3(0, 0, 0));
		r1.Tick(.5f);

		r2.Initialize();
		r2.SetPosition(math::Vector3(0, .9f, 0));
		r2.Tick(.5f);

		manifold = c1->DetectCollision(c2);
		ASSERT_NE(nullptr, manifold);
		ASSERT_TRUE(std::abs(0.1f - manifold->PenetrationDistance) < std::numeric_limits<float>::epsilon());
		delete manifold;

		r2.SetPosition(math::Vector3(0, 1.1f, 0));
		r2.Tick(.5f);

		manifold = c1->DetectCollision(c2);
		ASSERT_EQ(nullptr, manifold);

		r2.SetPosition(math::Vector3(0, -.6f, 0));
		r2.Tick(.5f);

		manifold = c1->DetectCollision(c2);

		ASSERT_TRUE(std::abs(0.4f - manifold->PenetrationDistance) < std::numeric_limits<float>::epsilon());
		delete manifold;

			
		// Test x axis
		r2.SetPosition(math::Vector3(.9f, 0, 0));
		r2.Tick(.5f);
		manifold = c1->DetectCollision(c2);

		ASSERT_TRUE(std::abs(0.1f - manifold->PenetrationDistance) < std::numeric_limits<float>::epsilon());
		delete manifold;

		r2.SetPosition(math::Vector3(1.1f, 0, 0));
		r2.Tick(.5f);

		manifold = c1->DetectCollision(c2);
		ASSERT_NE(nullptr, manifold);

		r2.SetPosition(math::Vector3(-0.6f, 0, 0));
		r2.Tick(.5f);

		manifold = c1->DetectCollision(c2);

		ASSERT_TRUE(std::abs(0.4f - manifold->PenetrationDistance) < std::numeric_limits<float>::epsilon());
		delete manifold;

		// Test z axis
		r2.SetPosition(math::Vector3(0, 0, 0.9f));
		r2.Tick(.5f);
		manifold = c1->DetectCollision(c2);

		ASSERT_TRUE(std::abs(0.1f - manifold->PenetrationDistance) < std::numeric_limits<float>::epsilon());
		delete manifold;

		r2.SetPosition(math::Vector3(0, 0, 1.1f));
		r2.Tick(.5f);

		manifold = c1->DetectCollision(c2);
		ASSERT_EQ(nullptr, manifold);

		r2.SetPosition(math::Vector3(0, 0, -0.6f));
		r2.Tick(.5f);

		manifold = c1->DetectCollision(c2);

		ASSERT_TRUE(std::abs(0.4f - manifold->PenetrationDistance) < std::numeric_limits<float>::epsilon());
		delete manifold;
	}

}
//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/gameplay_framework/Transform.h"

using namespace core;

namespace EngineCoreTests {

	TEST(TestTransforms, PositionTest) {
		Transform parent({5,5,5});
		Transform t1({ 1,0,0 }, &parent);
		Transform t2({ -1,0,0 }, &parent);

		//Test SetLocalPosition on leaf node
		t1.SetLocalPosition(t1.GetLocalPosition() + math::Vector3(1, 0, 0));
		ASSERT_EQ(math::Vector3(2, 0, 0), t1.GetLocalPosition());

		t1.SetPosition(math::Vector3(5, 5, 5));
		ASSERT_EQ(math::Vector3(0, 0, 0), t1.GetLocalPosition());
		ASSERT_EQ(math::Vector3(5, 5, 5), t1.GetPosition());

		parent.SetPosition({ 10, 10, 10 });
		ASSERT_EQ(math::Vector3(0, 0, 0), t1.GetLocalPosition());
		ASSERT_EQ(math::Vector3(10, 10, 10), t1.GetPosition());
		ASSERT_EQ(math::Vector3(10, 10, 10), parent.GetPosition());
		ASSERT_EQ(math::Vector3(10, 10, 10), parent.GetLocalPosition());
	}

	TEST(TestTransforms, RotationTest) {
		Transform parent(math::Rotator(0,0,0));
		Transform t1({ 1,0,0 }, &parent);
		Transform t2({ -1,0,0 }, &parent);
	}
}
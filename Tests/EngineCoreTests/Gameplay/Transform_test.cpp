//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/gameplay_framework/Transform.h"

using namespace core;

namespace EngineCoreTests {

	TEST(TestTransforms, PositionTest) {
		Transform parent(math::Vector3(5,5,5));
		Transform t1(math::Vector3(1,0,0), &parent);
		Transform t2(math::Vector3(-1,0,0), &parent);

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
		Transform t1({1, 0, 0}, math::Rotator(0, 90, 0), &parent);
		Transform t2({ 1, 0, 0 }, math::Rotator(0,0,0), &parent);
		Transform t3({ 1, 0, 0 }, math::Rotator(0,0,0), &t2);
		ASSERT_EQ(t1.GetRotation(), t2.GetRotation());

		parent.SetRotation(math::Rotator(0, 90, 0));
		
		//Check rotation hierarchy
		ASSERT_EQ(math::Quaternion(math::Rotator(0, 90, 0)), t1.GetLocalRotation());
		ASSERT_EQ(math::Quaternion(math::Rotator(0, 180, 0)), t1.GetRotation());
		ASSERT_EQ(math::Vector3(0, 0, -1), t1.GetPosition());

		//Check global position is rotated with parent
		auto t3Local = t3.GetLocalPosition();
		auto t3World = t3.GetPosition();
		ASSERT_EQ(math::Vector3(1, 0, 0), t3.GetLocalPosition());
		ASSERT_EQ(math::Vector3(0, 0, -2), t3.GetPosition());

		parent.SetRotation(math::Rotator(90, 0, 0));
		ASSERT_EQ(math::Vector3(1, 0, 0), t3.GetLocalPosition());
		ASSERT_EQ(math::Vector3(0, 2, 0), t3.GetPosition());
	}
}
//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/gameplay_framework/Transform.h"
#include "core/gameplay_framework/Entity.h"

using namespace core;

namespace EngineCoreTests {

	TEST(TestTransforms, PositionTest) {
		Entity parent;
		parent.SetPosition({ 5, 5, 5 });

		Entity t1;
		t1.SetParent(&parent);
		t1.SetLocalPosition({ 1, 0, 0 });

		Entity t2;
		t2.SetParent(&parent);
		t2.SetLocalPosition({ -1, 0, 0 });

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
		Entity parent;
		parent.SetPosition({0,0,3});
		parent.SetRotation(math::Rotator(90, 0, 0));

		Entity child;
		child.SetParent(&parent);
		child.SetLocalPosition({ 0, 0, 40 });

		ASSERT_EQ(math::Vector3(0, -40, 3), child.GetPosition());
		
		auto childLookDirection = child.m_Transform.GetForward().Normalize();
		auto translationVector = (parent.GetPosition() - child.GetPosition()).Normalize();

		ASSERT_EQ(childLookDirection, translationVector);
	}
}
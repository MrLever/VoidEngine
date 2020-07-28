//STD Headers
#include <cstddef>
#include <array>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/reflection/Reflection.h"

namespace rttr_test {
	CLASS()
	class User {
	public:
		ENABLE_RTTR()

		PROPERTY()
		int m_ID;

		PROPERTY()
		double m_Money;

		CTOR()
		User() {
			m_ID = 0;
			m_Money = 0;
			m_PrivateProperty = 0;
		}

		FUNCTION()
		virtual bool Modify(int i, int j) {
			m_ID += i;
			return true;
		}

	private:
		int m_PrivateProperty;
	};

	CLASS()
	class Player : public User {
	public:
		ENABLE_RTTR()

		PROPERTY()
		int m_XP;

		CTOR()
		Player() {
			m_XP = 0;
		}

	private:
		FUNCTION()
		bool Modify(int i, int j) override {
			User::Modify(i, j);
			m_Money += j;
			return true;
		}

		FUNCTION()
		int GainXP(int amount) {
			m_XP += amount;
		}
	};

}

utils::ClassDescriptor rttr_test::User::s_TypeInfo(
	utils::Name("rttr_test::User"),
	sizeof(rttr_test::User),
	std::make_shared<utils::ClassData<2,1,0>>(
		std::array<utils::Property, 2> { 
			DECL_PROP(rttr_test::User, int, m_ID),
			DECL_PROP(rttr_test::User, double, m_Money)
        },
		std::array<utils::Function, 1>{ utils::Name("Modify") }
    )
);

utils::ClassDescriptor rttr_test::Player::s_TypeInfo{
	utils::Name("rttr_test::Player"),
	sizeof(rttr_test::Player),
	std::make_shared<utils::ClassData<1,0,1>>(
		std::array<utils::Property, 1>{
			DECL_PROP(rttr_test::Player, int, m_XP)
		},
		std::array<utils::Function, 0>{},
		std::array<const utils::ClassDescriptor*, 1>{
			&utils::reflection::TypeResolver<rttr_test::User>::GetClass()
		}
	)
};

using namespace utils;

namespace utils_tests {
	
	TEST(RTTR_Tests, PrimitiveReflectionTest) {
		auto intRefl = reflection::TypeResolver<int>::GetType();
		ASSERT_EQ(sizeof(int), intRefl.m_Size);

		auto floatRefl = reflection::TypeResolver<int>::GetType();
		ASSERT_EQ(sizeof(float), floatRefl.m_Size);
	}

	TEST(RTTR_Tests, ClassDescriptorPropertyCountTest) {
		auto userRefl = reflection::TypeResolver<rttr_test::User>::GetClass();
		ASSERT_EQ(2, userRefl.GetPropertyCount());
		
		auto playerRefl = reflection::TypeResolver<rttr_test::Player>::GetClass();
		ASSERT_EQ(3, playerRefl.GetPropertyCount());
	}

	TEST(RTTR_Tests, ClassDescriptorPropertyReflectionAccessTest) {
		//Base class reflection
		auto userRefl = reflection::TypeResolver<rttr_test::User>::GetClass();
		auto idProp = userRefl.GetProperty(utils::Name("m_ID")).value();
		ASSERT_EQ("int", idProp.m_Type.m_Name);
		ASSERT_EQ("m_ID", idProp.m_Name);

		////Derived class reflection
		auto playerRefl = reflection::TypeResolver<rttr_test::Player>::GetClass();
		auto playerIdProp = playerRefl.GetProperty(utils::Name("m_ID")).value();
		ASSERT_EQ("m_ID", playerIdProp.m_Name);

		auto playerXPProp = playerRefl.GetProperty(utils::Name("m_XP")).value();
		ASSERT_EQ("m_XP", playerXPProp.m_Name);
	}

	TEST(RTTR_Tests, ClassDescriptorPropertyDataAccessTest) {
		rttr_test::User instance;

		auto userRefl = reflection::TypeResolver<rttr_test::User>::GetClass();

		instance.m_ID = 0;
		userRefl.SetPropertyData(&instance, utils::Name("m_ID"), 12345);
		ASSERT_EQ(12345, instance.m_ID);

		instance.m_ID = 123456;
		int id = userRefl.GetPropertyData<int>(&instance, utils::Name("m_ID")).value();
		ASSERT_EQ(123456, id);

		////Polymorphic class data access dest
		std::unique_ptr<rttr_test::User> polyInstance = std::make_unique<rttr_test::Player>();
		auto playerRefl = reflection::TypeResolver<rttr_test::Player>::GetClass();

		polyInstance->m_ID = 1234;
		auto playerID = playerRefl.GetPropertyData<int>(polyInstance.get(), utils::Name("m_ID"));
		ASSERT_EQ(1234, playerID);
		
		playerRefl.SetPropertyData(polyInstance.get(), utils::Name("m_ID"), 1);
		ASSERT_EQ(1, polyInstance->m_ID);

		dynamic_cast<rttr_test::Player*>(polyInstance.get())->m_XP = 1337;
		auto xpVal = playerRefl.GetPropertyData<int>(polyInstance.get(), utils::Name("m_XP"));
		ASSERT_EQ(true, xpVal.has_value());
		ASSERT_EQ(1337, xpVal.value());

		playerRefl.SetPropertyData<int>(polyInstance.get(), utils::Name("m_XP"), 0);
		ASSERT_EQ(0, dynamic_cast<rttr_test::Player*>(polyInstance.get())->m_XP);
	}
	
	TEST(RTTR_Tests, StringToTypeDescriptorTest) {
		ASSERT_FALSE(true);
	}

	TEST(RTTR_Tests, StringToClassDescriptorTest) {
		ASSERT_FALSE(true);
	}

	TEST(RTTR_Tests, TypeReificationTest) {
		ASSERT_FALSE(true);
	}
}
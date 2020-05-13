//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/TypeUtils.h"

using namespace utils;

namespace utils_tests {
	class Person {
		ENABLE_RTTI(Person)
	};

	class DummyParent : Person {
		ENABLE_RTTI(DummyParent)
	};

	class DummyChild : public DummyParent {
		ENABLE_RTTI(DummyChild)
	};

	class DummyStranger {
		ENABLE_RTTI(DummyStranger)
	};

	TEST(RTTI_Tests, TypenameTest) {
		DummyParent* mom = new DummyParent();
		DummyParent* dad = new DummyParent();
		DummyParent* stupidKid = new DummyChild();
		DummyStranger* stranger = new DummyStranger();

		
		ASSERT_EQ(utils::Name("DummyParent"), mom->GetTypename());
		ASSERT_EQ(DummyParent::GetStaticTypename(), mom->GetTypename());
		ASSERT_EQ(mom->GetTypename(), dad->GetTypename());

		ASSERT_EQ(utils::Name("DummyChild"), stupidKid->GetTypename());
		ASSERT_EQ(DummyChild::GetStaticTypename(), stupidKid->GetTypename());

		ASSERT_EQ(utils::Name("DummyStranger"), stranger->GetTypename());
		ASSERT_EQ(DummyStranger::GetStaticTypename(), stranger->GetTypename());
	}

	TEST(RTTI_Tests, IsTest) {
		DummyParent* mom = new DummyParent();
		DummyParent* dad = new DummyParent();
		DummyParent* stupidKid = new DummyChild();
		DummyStranger* stranger = new DummyStranger();

		ASSERT_TRUE(mom->Is<DummyParent>());
		ASSERT_TRUE(dad->Is<DummyParent>());
		ASSERT_TRUE(mom->Is<Person>());

		ASSERT_TRUE(stupidKid->Is<DummyParent>());
		ASSERT_TRUE(stupidKid->Is<Person>());

		ASSERT_FALSE(stranger->Is<DummyParent>());
	}

	TEST(RTTI_Tests, AsTest) {
	
	}

}
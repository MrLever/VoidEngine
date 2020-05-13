//STD Headers
#include <fstream>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/threading/ThreadPool.h"

using namespace utils;

namespace utils_tests {

	int testFunc() {
		const int UniversalAnswer = 42;
		return UniversalAnswer;
	}

	int testFunc2(int a, int b) {
		return a + b;
	}


	TEST(ThreadPoolTests, SubmitFreeFunctionJobTest) {
		ThreadPool p;

		//Nonmember noarg function test
		auto res = p.SubmitJob(testFunc);
		ASSERT_EQ(42, res.get());

		//Nonmember arg function test
		auto res2 = p.SubmitJob(testFunc2, 1, 2);
		ASSERT_EQ(3, res2.get());
	}

	TEST(ThreadPoolTests, SubmitLambdaJobTest) {
		ThreadPool p;

		//Lambda noarg test
		auto res = p.SubmitJob(
			[] {
				return "hello";
			}
		);
		ASSERT_STREQ("hello", res.get());


		//Lamba no arg capture local test
		int a, b;
		a = b = 5;
		auto res2 = p.SubmitJob(
			[a, b] {
				return a + b;
			}
		);
		ASSERT_EQ(10, res2.get());

		//Lambda arg test
		auto res3 = p.SubmitJob(
			[](int a, int b) {
				return a + b;
			},
			5, 5
		);
		ASSERT_EQ(10, res3.get());
	}

	TEST(ThreadPoolTests, SubmitMemberFunctionJobTest) {
		ThreadPool p;

		class DummyObject {
		public:
			int a;
			int b;

			DummyObject() {
				a = b = 5;
			}

			int DummyAdd() {
				return a + b;
			}

			int ParamAdd(int c, int d) {
				return c + d;
			}
		};

		DummyObject d;

		auto res = p.SubmitJob(
			[&]() {	return d.DummyAdd(); }
		);
		ASSERT_EQ(10, res.get());

		auto res2 = p.SubmitJob(
			[&]() { return d.ParamAdd(1, 2); }
		);
		ASSERT_EQ(3, res2.get());

		DummyObject* ptr = new DummyObject();

		auto res3 = p.SubmitJob(
			[&]() { return ptr->DummyAdd(); }
		);
		ASSERT_EQ(10, res3.get());

		auto res4 = p.SubmitJob(
			[&]() { return ptr->ParamAdd(1, 2); }
		);
		ASSERT_EQ(3, res4.get());

		delete(ptr);
	}
};
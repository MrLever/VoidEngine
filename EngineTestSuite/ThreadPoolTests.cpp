//STD Headers
#include <fstream>

//Library Headers
#include "stdafx.h"
#include "CppUnitTest.h"

//Void Engine Headers
#include "ThreadPool.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineTestSuite {

	int testFunc() {
		const int UniversalAnswer = 42;
		return UniversalAnswer;
	}

	int testFunc2(int a, int b) {
		return a + b;
	}

	TEST_CLASS(ThreadPoolTests) {
	public:

		TEST_METHOD(SubmitFreeFunctionJobTest) {
			ThreadPool p;

			//Nonmember noarg function test
			auto res = p.SubmitJob(testFunc);
			Assert::AreEqual(42, res.get());

			//Nonmember arg function test
			auto res2 = p.SubmitJob(testFunc2, 1, 2);
			Assert::AreEqual(3, res2.get());
		}

		TEST_METHOD(SubmitLambdaJobTest) {
			ThreadPool p;

			//Lambda noarg test
			auto res = p.SubmitJob(
				[] {
					return "hello";
				}
			);
			Assert::AreEqual("hello", res.get());


			//Lamba no arg capture local test
			int a, b;
			a = b = 5;
			auto res2 = p.SubmitJob(
				[a, b] {
					return a + b;
				}
			);
			Assert::AreEqual(10, res2.get());

			//Lambda arg test
			auto res3 = p.SubmitJob(
				[](int a, int b) {
					return a + b;
				},
				5, 5
			);
			Assert::AreEqual(10, res3.get());
		}

		TEST_METHOD(SubmitMemberFunctionJobTest) {
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

			auto res = p.SubmitJob(std::bind(&DummyObject::DummyAdd, &d));
			Assert::AreEqual(10, res.get());

			auto res2 = p.SubmitJob(std::bind(&DummyObject::ParamAdd, &d, 1, 2));
			Assert::AreEqual(3, res2.get());
		}

		TEST_METHOD(ThreadPoolStressTest) {
			ThreadPool p;

			//A recursive fibonacci function, meant to eat up time.
			std::function<int(int)> stressFunction;
			stressFunction = [&stressFunction](int n) {
				if (n == 0) return 0;
				if (n == 1) return 1;

				return stressFunction(n - 1) + stressFunction(n - 2);
			};

			int desired = stressFunction(25);

			//Push 500 very expensive jobs into the thread pool all at once
			//500 is not a lot, but since it is a unit test, it cannot spend forever working on this.
			const int numTrials = 500;
			std::vector<std::future<int>> results;
			for (int i = 0; i < numTrials; i++) {
				results.push_back(p.SubmitJob(stressFunction, 25));
			}

			//Assert that every job has finished and has the correct result.
			for (auto &x : results) {
				Assert::AreEqual(desired, x.get());
			}
		}
	};

	TEST_CLASS(ThreadSafeQueueTests) {
	public:
		TEST_METHOD(SizeTest) {
			ThreadSafeQueue <int> q;
			q.push(5);
			Assert::AreEqual(1, q.size());
			q.push(1);
			Assert::AreEqual(2, q.size());
			q.pop();
			Assert::AreEqual(1, q.size());
		}

		TEST_METHOD(PushTest) {
			ThreadSafeQueue <int> q;
			
			int size = q.size();
			q.push(5);
			int size2 = q.size();

			Assert::AreNotEqual(size, size2);
		}
		
		TEST_METHOD(PopNoResultReturnTest) {
			ThreadSafeQueue <int> q;
			q.push(5);
			
			int size = q.size();
			q.pop();
			int size2 = q.size();

			Assert::IsTrue(size > size2);
		}
		
		TEST_METHOD(PopResultReturnTest) {
			ThreadSafeQueue <int> q;
			q.push(5);

			int res;

			q.pop(res);

			Assert::AreEqual(5, res);
		}
	};
}
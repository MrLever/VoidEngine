//STD Headers
#include <fstream>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/threading/ThreadSafeQueue.h"


using namespace utils;

namespace utils_tests {

	TEST(ThreadSafeQueueTests, SizeTest) {
		ThreadSafeQueue <int> q;
		
		q.push(5);
		ASSERT_EQ(1, q.size());
		
		q.push(1);
		ASSERT_EQ(2, q.size());
		
		q.pop();
		ASSERT_EQ(1, q.size());
	}

	TEST(ThreadSafeQueueTests, PushTest) {
		ThreadSafeQueue <int> q;

		int size = q.size();
		q.push(5);
		int size2 = q.size();

		ASSERT_NE(size, size2);
	}

	TEST(ThreadSafeQueueTests, PopNoResultReturnTest) {
		ThreadSafeQueue <int> q;
		q.push(5);

		int size = q.size();
		q.pop();
		int size2 = q.size();

		ASSERT_TRUE(size > size2);
	}

	TEST(ThreadSafeQueueTests, PopResultReturnTest) {
		ThreadSafeQueue <int> q;
		q.push(5);

		int res;

		q.pop(res);

		ASSERT_EQ(5, res);
	}

}
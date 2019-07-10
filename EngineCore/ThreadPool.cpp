//STD Headers

//Library Headers

//Void Engine Headers
#include "ThreadPool.h"

namespace EngineUtils {

	ThreadPool::ThreadPool() : NumThreads(std::thread::hardware_concurrency() - 1), Terminated(false) {

	}

	ThreadPool::ThreadPool(int numThreads) : NumThreads(NumThreads), Terminated(false) {
	
	}

	ThreadPool::~ThreadPool() {
		Terminate();
	}

	void ThreadPool::Terminate() {
		Terminated = true;
	}

	inline bool ThreadPool::QueryIsTerminated() const {
		return Terminated;
	}

}
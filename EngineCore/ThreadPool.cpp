//STD Headers

//Library Headers

//Void Engine Headers
#include "ThreadPool.h"

namespace EngineUtils {

	ThreadPool::ThreadPool() : NumThreads(std::thread::hardware_concurrency() - 1) {

	}

	ThreadPool::ThreadPool(int numThreads) : NumThreads(NumThreads){
	
	}

	ThreadPool::~ThreadPool() {
	}

}
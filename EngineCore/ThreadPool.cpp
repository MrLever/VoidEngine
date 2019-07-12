//STD Headers

//Library Headers

//Void Engine Headers
#include "ThreadPool.h"
#include "ThreadPoolWorker.h"

namespace EngineUtils {

	///Public
	ThreadPool::ThreadPool() : NumThreads(std::thread::hardware_concurrency() - 1),	Terminated(false){
		StartThreads();
	}

	ThreadPool::ThreadPool(int numThreads) : NumThreads(numThreads), Terminated(false) {
		StartThreads();
	}

	ThreadPool::~ThreadPool() {
		Terminate();
	}

	void ThreadPool::Terminate() {
		Terminated = true;

		WorkSignal.notify_all();

		for (auto &thread : WorkerThreads) {
			if (thread.joinable()) {
				thread.join();
			}
		}
	}

	///Private
	inline bool ThreadPool::QueryIsTerminated() const {
		return Terminated;
	}

	void ThreadPool::StartThreads() {
		for (auto i = 0; i < NumThreads; i++) {
			WorkerThreads.emplace_back(ThreadPoolWorker(this, i));
		}
	}

}
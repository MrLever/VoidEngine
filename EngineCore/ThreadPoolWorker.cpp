//STD Headers

//Library Headers

//Void Engine Headers
#include "ThreadPool.h"
#include "ThreadPoolWorker.h"

namespace utils {
	ThreadPoolWorker::ThreadPoolWorker(ThreadPool* masterPool, int id) : Pool(masterPool), ID(id) {

	}

	void ThreadPoolWorker::operator() ( ) {
		std::function<void()> job = nullptr;
		bool jobAquired = false;

		while (!Pool->Terminated) {
			
			{ //Smaller scope to trigger the RAII features of the unique_lock
				std::unique_lock<std::mutex> queueLock(Pool->QueueLock);

				//If there is no work to do
				if (Pool->WorkQueue.size() == 0) {
					Pool->WorkSignal.wait(queueLock);
				}

				//Pop job off of queue and store result in job
				jobAquired = Pool->WorkQueue.pop(job);
			}

			if (jobAquired && job != nullptr) {
				job();
			}
		}
	}
}
#pragma once
//STD Headers
#include <thread>
#include <functional>

//Library Headers

//Void Engine Headers
#include "ThreadPool.h"
#include "ThreadSafeQueue.h"

namespace EngineUtils {

	/**
	 * A threadpool worker runs on an infinite loop until the threadpool is shut down.
	 * A worker continually grabbs and executes jobs from it's parent Threadpool.
	 * If the pool has no queued jobs, the worker will sleep until notified of new jobs.
	 * "Inspired" by https://github.com/progschj/ThreadPool
	 * and https://github.com/mtrebi/thread-pool
	 */
	class ThreadPoolWorker {
	public:
		///CTORS

		/**
		 * Constructor
		 * @param masterPool The owning threadpool of this worker
		 * @param id This worker's id
		 */
		ThreadPoolWorker(ThreadPool* masterPool, int id);

		/// Operator Overloads
		/**
		 * Function call operator
		 * This function will run on the thread until the thread is to be destroyed
		 */
		void operator() ( );

	private:
		ThreadPool* Pool;
		int ID;
	};
}
#pragma once
//STD Headers
#include <atomic>
#include <future>
#include <thread>

//Library Headers

//Void Engine Headers
#include "ThreadSafeQueue.h"

namespace EngineUtils {

	/**
	 * The threadpool is responsible for accepting and executing jobs asynchronously for engine systems.
	 * "Inspired" by https://github.com/progschj/ThreadPool
	 * and https://github.com/mtrebi/thread-pool
	 */
	class ThreadPool {
	public:

		friend class ThreadPoolWorker;

		///CTORS
		/**
		 * Default Constructor
		 */
		ThreadPool();

		/**
		 * Default Constructor
		 * @param numThreads The number of threads to construct for the pool
		 */
		ThreadPool(int numThreads);

		/**
		 * Destructor
		 * Terminates all worker threads
		 */
		~ThreadPool();

		///Public Member Function
		/**
		 * Variadic template function that submits work to be executed on an abritray thread
		 * @param f Universal reference to a function
		 * @param Args... A variable number of arguments to f
		 * @return A future of type decltype(f(args...)) to the result of f
		 */
		template<class F, class... Args>
		auto SubmitJob(F&& f, Args&& ... args) -> std::future<decltype(f(args...))>;

		/**
		 * A query for whether the thread pool has been terminated
		 * @return this->Terminated;
		 */
		inline bool QueryIsTerminated() const;

		/**
		 * A query for whether the thread pool has been terminated
		 * @return this->Terminated;
		 */
		void Terminate();

	private:
		///Private class members
		/** Number of active threads in the pool */
		int NumThreads;

		/** Flag for the workers to query if the thread pool has been shut down */
		bool Terminated;

		/** Queue of submitted jobs to process */
		ThreadSafeQueue<std::function<void()>> WorkQueue;

		/** Lock for the work queue */
		std::mutex QueueLock;

		/** Conditionaly Variable the workers will wait on for more work */
		std::condition_variable WorkSignal;
	};

	///Template function definitions
	template<class F, class ...Args>
	inline auto ThreadPool::SubmitJob(F&& f, Args&& ...args) -> std::future<decltype(f(args ...))>
	{
		return std::future<decltype(f(args ...))>();
	}

}
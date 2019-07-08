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
		 */
		template<class F, class... Args>
		auto SubmitJob(F&& f, Args&& ... args) -> std::future<decltype(f(args...))>;

	private:
		/** Number of active threads in the pool */
		int NumThreads;

		/** Queue of submitted jobs to process */
		ThreadSafeQueue<std::function<void()>> WorkQueue;
	};

	///Template function definitions
	template<class F, class ...Args>
	inline auto ThreadPool::SubmitJob(F&& f, Args&& ...args) -> std::future<decltype(f(args ...))>
	{
		return std::future<decltype(f(args ...))>();
	}

}
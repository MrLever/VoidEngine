#pragma once
//STD Headers
#include <mutex>
#include <queue>

//Library Headers

//Void Engine Headers

namespace EngineUtils {
	/**
	 * Thread safe wrapper for std::queue
	 */
	template<typename T>
	class ThreadSafeQueue {
	public:
		///CTORS
		
		/**
		 * Constructor
		 */
		ThreadSafeQueue() = default;

		/**
		 * Destructor
		 */
		~ThreadSafeQueue() = default;

		/**
		 * Pushes an item onto the queue in a thread safe manner
		 * @param arg The item to push onto the queue
		 */
		void push(const T& arg);
		
		/**
		 * Removes an item from the queue
		 */
		void pop();

		/**
		 * Returns the size of the safe queue
		 * @return the number of elements in the queue
		 */
		int size() const;

	private:
		/** The protected queue */
		std::queue<T> SafeQueue;

		/** The queue's mutex */
		std::mutex QueueLock;
	};

	template<typename T>
	inline void ThreadSafeQueue<T>::push(const T& arg) {
		std::unique_lock<std::mutex>(QueueLock);
		SafeQueue.push(arg);
	}
	
	template<typename T>
	inline void ThreadSafeQueue<T>::pop() {
		std::unique_lock<std::mutex>(QueueLock);
		SafeQueue.pop();
	}
	
	template<typename T>
	inline int ThreadSafeQueue<T>::size() const {
		std::unique_lock<std::mutex>(QueueLock);
		return SafeQueue.size();
	}
}

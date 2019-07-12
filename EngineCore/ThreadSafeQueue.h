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
		bool push(const T& arg);
		
		/**
		 * Removes an item from the queue, does not return result
		 */
		bool pop();

		/**
		 * Removes an item from the queue
		 * @param res
		 */
		bool pop(T& res);

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
	inline bool ThreadSafeQueue<T>::push(const T& arg) {
		std::unique_lock<std::mutex>(QueueLock);
		SafeQueue.push(arg);
		return true;
	}

	template<typename T>
	inline bool ThreadSafeQueue<T>::pop() {
		std::unique_lock<std::mutex>(QueueLock);
		if (SafeQueue.empty()) {
			return false;
		}

		SafeQueue.pop();
		return true;
	}
	
	template<typename T>
	inline bool ThreadSafeQueue<T>::pop(T &res) {
		std::unique_lock<std::mutex>(QueueLock);
		if (SafeQueue.empty()) {
			return false;
		}

		res = std::move(SafeQueue.front());

		SafeQueue.pop();
		return true;
	}
	
	template<typename T>
	inline int ThreadSafeQueue<T>::size() const {
		std::unique_lock<std::mutex>(QueueLock);
		return static_cast<int>(SafeQueue.size());
	}
}

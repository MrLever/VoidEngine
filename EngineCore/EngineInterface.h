#pragma once
//STD Headers
#include <vector>

//Library Headers

//Void Engine Headers
#include "ResourceManager.h"
#include "ThreadPool.h"

namespace EngineCore{
	/*
	 * Provides an interface to EngineCore systems to leverage key EngineUtil dependencies
	 */
	class EngineInterface{
	public:
		/*
		 * @param threadPool The engine's main threadpool
		 * @param resourceManager The egine's main resourceManager
		 */
		EngineInterface(
			ThreadPoolPtr threadPool,
			ResourceManagerPtr resourceManager
		);

		/**
		 * Returns a shared_ptr to the Engine's thread pool
		 */
		ThreadPoolPtr GetThreadPool() const;

		/**
		 * Returns a shared_ptr to the Engine's Resource manager
		 */
		ResourceManagerPtr GetResourceManager() const;

	private:
		/** Shared pointer to the Engine's active threadpool */
		ThreadPoolPtr EngineThreadPool;

		/** Shared pointer to the Engine's active resource manager */
		ResourceManagerPtr EngineResourceManager;
	};

	using EngineInterfacePtr = std::shared_ptr<EngineInterface>;
}
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
		///CTORS
		/*
		 * @param threadPool The engine's main threadpool
		 * @param resourceManager The egine's main resourceManager
		 */
		EngineInterface(
			EngineUtils::ThreadPoolPtr threadPool,
			EngineUtils::ResourceManagerPtr resourceManager
		);

		///Public Member Functions
		/**
		 * Returns a shared_ptr to the Engine's thread pool
		 */
		EngineUtils::ThreadPoolPtr GetThreadPool() const;

		/**
		 * Returns a shared_ptr to the Engine's Resource manager
		 */
		EngineUtils::ResourceManagerPtr GetResourceManager() const;

	private:
		EngineUtils::ThreadPoolPtr EngineThreadPool;
		EngineUtils::ResourceManagerPtr EngineResourceManager;
	};

	using EngineInterfacePtr = std::shared_ptr<EngineInterface>;
}
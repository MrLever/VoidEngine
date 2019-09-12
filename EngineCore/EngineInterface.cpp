#include "EngineInterface.h"

namespace EngineCore {

	///CTORS
	EngineInterface::EngineInterface(ThreadPoolPtr threadPool,	ResourceManagerPtr resourceManager) 
		: EngineThreadPool(std::move(threadPool)), EngineResourceManager(std::move(resourceManager)) {
	
	}

	///Public Member Functions
	ThreadPoolPtr EngineInterface::GetThreadPool() const {
		return EngineThreadPool;
	}

	ResourceManagerPtr EngineInterface::GetResourceManager() const {
		return EngineResourceManager;
	}
}
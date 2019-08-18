#include "EngineInterface.h"

namespace EngineCore {

	///CTORS
	EngineInterface::EngineInterface(EngineUtils::ThreadPoolPtr threadPool,	EngineUtils::ResourceManagerPtr resourceManager) 
		: EngineThreadPool(std::move(threadPool)), EngineResourceManager(std::move(resourceManager)) {
	
	}

	///Public Member Functions
	EngineUtils::ThreadPoolPtr EngineInterface::GetThreadPool() const {
		return EngineThreadPool;
	}

	EngineUtils::ResourceManagerPtr EngineInterface::GetResourceManager() const {
		return EngineResourceManager;
	}
}
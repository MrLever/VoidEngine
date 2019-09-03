//STD Headers

//Library Headers

//Void Engine Headers
#include "ResourceHandle.h"

namespace EngineUtils {

	ResourceHandle::ResourceHandle(std::future<std::shared_ptr<Resource>>& resourceFuture)
		: RequestedResource(std::move(resourceFuture)) {
	}
	
	ResourceHandle::~ResourceHandle() {
	}

}
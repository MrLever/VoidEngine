//STD Headers

//Library Headers

//Void Engine Headers
#include "ResourceHandle.h"

namespace EngineUtils {
	ResourceHandle::ResourceHandle(std::shared_ptr<Resource> resource, std::promise<bool> &resourcePromise)
		: RequestedResource(resource) {

		ResourceReady = resourcePromise.get_future();
	}

	ResourceHandle::ResourceHandle(std::shared_ptr<Resource> resource, std::future<bool>& resourceFuture)
		: RequestedResource(resource), ResourceReady(std::move(resourceFuture)) {
	}
	
	ResourceHandle::~ResourceHandle() {
	}
}
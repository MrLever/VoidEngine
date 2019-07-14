//STD Headers

//Library Headers

//Void Engine Headers
#include "ResourceHandle.h"

namespace EngineUtils {
	ResourceHandle::ResourceHandle(
		std::shared_ptr<Resource> resource,
		std::promise<bool> &resourcePromise) {

		ResourceReady = resourcePromise.get_future();
	}
}
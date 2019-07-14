#pragma once
//STD Headers
#include <future>
#include <memory>

//Library Headers

//Void Engine Headers
#include "Resource.h"

namespace EngineUtils {
	/**
	 * The resource handle is a gatekeeper for resources requested
	 * from the resource manager. It forces requestors to wait 
	 * until the resource is loaded to use it.
	 */
	class ResourceHandle {
	public:
		///CTORS
		/**
		 * Constructor
		 * @param resourcePromise The promise used by the handles' future
		 */
		ResourceHandle(std::shared_ptr<Resource> resource, std::promise<bool>& resourcePromise);

		/**
		 * Constructor
		 * @param resourceFuture The promise used by the handles' future
		 */
		ResourceHandle(std::shared_ptr<Resource> resource, std::future<bool>& resourceFuture);

		///Public Member Functions
		/**
		 * Gets the resource that was loaded, or blocks until loading is finished
		 */
		template <typename T>
		std::shared_ptr<T> GetResource();

	private:
		/** Future to the resource to be loaded */
		std::future<bool> ResourceReady;
		std::shared_ptr<Resource> RequestedResource;
	};

	template<class T>
	inline std::shared_ptr<T> ResourceHandle::GetResource() {
		if (ResourceReady.get()) {
			return std::dynamic_pointer_cast<T>(RequestedResource);
		}
		else {
			return nullptr;
		}
	}
}
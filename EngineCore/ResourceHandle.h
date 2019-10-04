#pragma once
//STD Headers
#include <future>
#include <memory>

//Library Headers

//Void Engine Headers
#include "Resource.h"

namespace utils {
	/**
	 * The resource handle is a gatekeeper for resources requested
	 * from the resource manager. It forces requestors to wait 
	 * until the resource is loaded to use it.
	 */
	class ResourceHandle {
		friend class ResourceManager;
	public:
		/**
		 * Constructor
		 * @param resource The resource wrapped by this handle
		 * @param resourceFuture The future used by the handles' future
		 */
		ResourceHandle(std::future<std::shared_ptr<Resource>>& resourceFuture);

		/**
		 * Destructor
		 */
		~ResourceHandle();

		/**
		 * Gets the resource that was loaded, or blocks until loading is finished
		 * @return The resource requested, dynamically casted to the specified type
		 */
		template <typename T>
		std::shared_ptr<T> GetResource();

	private:
		/** Future to the resource to be loaded */
		std::shared_future<std::shared_ptr<Resource>> RequestedResource;		 
	};

	template<class T>
	inline std::shared_ptr<T> ResourceHandle::GetResource() {
		auto genericResource = RequestedResource.get();
		
		auto resource = std::dynamic_pointer_cast<T>(genericResource);
		if (resource == nullptr) {
			std::cout << "***ERROR*** Invalid resource request";
		}

		return resource;
	}
}
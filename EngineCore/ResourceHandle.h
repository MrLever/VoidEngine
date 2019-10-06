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
	template <class T>
	class ResourceHandle {
	public:
		/**
		 * Constructor
		 * @param resource The resource wrapped by this handle
		 * @param resourceFuture The future used by the handles' future
		 */
		ResourceHandle(std::future<std::shared_ptr<T>>& resourceFuture);

		/**
		 * Destructor
		 */
		~ResourceHandle() = default;

		std::shared_ptr<T> GetResource();

	private:
		/** Future to the resource to be loaded */
		std::shared_future<std::shared_ptr<T>> RequestedResource;		 
	};

	template<class T>
	inline ResourceHandle<T>::ResourceHandle(std::future<std::shared_ptr<T>>& resourceFuture)
	: RequestedResource(std::move(resourceFuture)){

	}

	template<class T>
	inline std::shared_ptr<T> ResourceHandle<T>::GetResource() {
		return RequestedResource.get();
	}
}
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
		friend class ResourceManager;
	public:
		///CTORS
		/**
		 * Constructor
		 * @param resource The resource wrapped by this handle
		 * @param resourcePromise The promise used by the handles' future
		 */
		ResourceHandle(std::shared_ptr<Resource> resource, std::promise<bool>& resourcePromise);

		/**
		 * Constructor
		 * @param resource The resource wrapped by this handle
		 * @param resourceFuture The future used by the handles' future
		 */
		ResourceHandle(std::shared_ptr<Resource> resource, std::future<bool>& resourceFuture);

		/**
		 * Destructor
		 */
		~ResourceHandle();

		///Public Member Functions
		/**
		 * Gets the resource that was loaded, or blocks until loading is finished
		 * @return The resource requested, dynamically casted to the specified type
		 */
		template <typename T>
		std::shared_ptr<T> GetResource();

	private:
		/** Future to the resource to be loaded */
		std::shared_future<bool> ResourceReady;

		/** Shared base pointer to the resource requested */
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
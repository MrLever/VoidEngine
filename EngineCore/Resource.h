#pragma once
//STD Headers
#include <atomic>
#include <string>
#include <filesystem>

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace EngineUtils {
	/**
	 * Resources are the objects handled by the resource manager.
	 */
	class Resource {
	public:
		///CTORS
		/**
		 * Constructor
		 * @param filePath the resources location
		 */
		Resource(const std::string& filePath);
		
		/**
		 * Destructor
		 */
		virtual ~Resource();

		/**
		 * Loads a given resource from main memory
		 */
		virtual bool Load() = 0;

		/**
		 * Loads the resource's defualt value if the path provided is invalid
		 */
		virtual bool LoadErrorResource() = 0;

		bool GetResourceValid();

		/**
		 * Gets the resources' ID
		 */
		Name GetResourceID();

	protected:
		/** Unique identifier for resource lookup and comparison */
		Name ResourceID;

		/** Path to the desired resource */
		std::filesystem::path ResourcePath;

		/** Flag specifying if the resource was found in main memory */
		std::atomic<bool> ResourceValid;
	};
}

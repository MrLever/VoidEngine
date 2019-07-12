#pragma once
//STD Headers
#include <string>
#include <filesystem>

//Library Headers

//Void Engine Headers
#include "UUID.h"

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
		virtual void Load() = 0;

		/**
		 * De-allocates resource data from memory
		 */
		virtual void Unload() = 0;



	protected:
		/** Unique identifier for resource lookup and comparison */
		UUID ResourceID;

		/** Path to the desired resource */
		std::filesystem::path ResourcePath;

		/** Flag specifying if the resource was found in main memory */
		bool ResourceValid;

	};
}

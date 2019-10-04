#pragma once
//STD Headers
#include <string>
#include <vector>

//Library Headers

//Void Engine Headers
#include "Resource.h"

namespace utils{
	//Forward class declarations
	class ResourceManager;

	/**
	 * @class PackageResource
	 * @brief The package class represents a resource that requires 1 to many 
	 *        child resources to also be loaded.
	 */
	class PackageResource {
	public:
		/**
		 * Constructor
		 */
		PackageResource(const std::string& filePath);

		virtual void Load() = 0;

		virtual void GetResources() = 0;

	private:
		/** Path to the package's data */
		std::string FilePath;

		std::vector<std::string> ResourcePaths;
	};
}


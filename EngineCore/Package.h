#pragma once
//STD Headers
#include <string>
#include <vector>

//Library Headers

//Void Engine Headers

namespace utils{
	/**
	 * @class Package
	 * @brief The package class represents a resource that requires 1 to many 
	 *        child resources to also be loaded.
	 */
	class Package{
	public:
		/**
		 * Constructor
		 */
		Package(const std::string& filePath);

		virtual void Load() = 0;

		virtual void GetResources() = 0;

		void Initialize();



	private:
		/** Path to the package's data */
		std::string FilePath;

		std::vector<std::string> ResourcePaths;
		

	};
}


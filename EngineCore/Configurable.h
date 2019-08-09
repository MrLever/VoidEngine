#pragma once
//STD Headers
#include <memory>
#include <compare>

//Library Headers

//Void Engine Headers
#include "Configuration.h"
#include "UUID.h"
#include "ResourceManager.h"


namespace EngineUtils {
	
	/**
	 * Configurable is an abstract base class that allows implementers to load and use configuration scripts
	 */
	class Configurable {
	public:
		/**
		 * Constructor
		 * @param name The name of the configurable object
		 * @param configFile The configuration file used by the configurable object
		 * @param resourceManager The resource manager this object depends on to load resources
		 */
		Configurable(std::string name, std::string configFile, std::shared_ptr<ResourceManager> resourceManager);
		
		/**
		 * Three way comparison operator overload
		 * @param other The configurable to compare to this
		 */
		std::strong_ordering operator<=>(const Configurable& other) const;

		/**
		 * Instructs the resource manager to begin loading the configuration file
		 */
		virtual void LoadConfiguration();

		/**
		 * Abstract function to ensure all subclasses define configuration behavior
		 */
		virtual void Configure() = 0;


	protected:
		/** The unique ID of this configurable object */
		UUID ID;

		/** The file*/
		std::string ConfigFilePath;

		/** The configuration resource to be used by this object */
		std::shared_ptr<Configuration> Config;

		/** The resource manager to be used by this object */
		std::shared_ptr<ResourceManager> ResourceMngr;
	};
}
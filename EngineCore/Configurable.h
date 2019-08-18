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
	 * Configurable is an abstract base class that allows implementers to 
	 * load and use configuration scripts
	 */
	class Configurable {
	public:
		/**
		 * Constructor
		 * @param name The name of the configurable object
		 * @param configFile The configuration file used by the configurable object
		 * @param resourceManager The resource manager this object depends on to load resources
		 */
		Configurable(const std::string& configFile, std::shared_ptr<ResourceManager> resourceManager);
		
		/**
		 * Instructs the resource manager to begin loading the configuration file
		 */
		virtual void LoadConfiguration();

		/**
		 * Instructs the resource manager to begin reloading the configuration file
		 */
		virtual void ReloadConfiguration();

		/**
		 * Allows the caller to instruct this object to load and apply a new configuration
		 */
		virtual void Reconfigure(const std::string& newConfigFilePath);

		/**
		 * Pure virtual function to ensure all subclasses define configuration behavior
		 */
		virtual void Configure() = 0;

	protected:
		/** The file path to the Configurable's configuration */
		std::string ConfigFilePath;

		/** The configuration resource to be used by this object */
		std::shared_ptr<Configuration> Config;

		/** The resource manager to be used by this object */
		std::shared_ptr<ResourceManager> ResourceMngr;
	};
}
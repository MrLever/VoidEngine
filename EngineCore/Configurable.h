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
		Configurable(
			const std::string& name, 
			const std::string& configFile, 
			std::shared_ptr<ResourceManager> resourceManager
		);
		
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

		/**
		 * Allows callers to request this Configurable's unique ID
		 */
		UUID GetUUID();

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
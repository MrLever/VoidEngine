//STD Headers
#include <memory>
#include <vector>

//Library Headers

//Void Engine Headers
#include "ResourceManager.h"

namespace EngineUtils {

	/** Forward Declaration of Configurable class */
	class Configurable;

	class ConfigManager {
	public:
		/**
		 * Constructor
		 * @param resourceManager The resource manager this config manager depends on for config loading
		 */
		ConfigManager(std::shared_ptr<ResourceManager> resourceManager);

		void RegisterConfigurable(Configurable* user);

	private:
		/** The resource manager this object depends on to load configurations */
		std::shared_ptr<ResourceManager> GameResourceManager;

		/** List of configurable objects that rely on this configuration manager */
		std::vector<Configurable*> Users;

	};

}
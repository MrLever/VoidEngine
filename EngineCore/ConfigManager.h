//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "ResourceManager.h"

namespace EngineUtils {

	class ConfigManager {
	public:
		ConfigManager(std::shared_ptr<ResourceManager> resourceManager);

	private:
		std::shared_ptr<ResourceManager> GameResourceManager;
	};

}
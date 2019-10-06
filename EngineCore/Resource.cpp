//STD Headers

//Library Headers

//Void Engine Headers
#include "Resource.h"
#include "Logger.h"

namespace utils {
	///Public Functions
	Resource::Resource(const std::string& filePath) 
		: ResourceID(filePath), ResourcePath(filePath), IsInitialized(false), IsThreadSafe(false), IsComposite(false) {
		
		ResourceValid = std::filesystem::exists(ResourcePath);
		if (!ResourceValid) {
			utils::Logger::LogWarning("Resource located at [" + filePath + "] not found");
		}
	}

	Resource::~Resource() {

	}

	void Resource::AttatchThreadPool(ThreadPoolPtr pool) {
		GameThreadPool = std::move(pool);
	}

	bool Resource::IsValid() {
		return ResourceValid;
	}

	bool Resource::GetIsComposite() {
		return IsComposite;
	}

	Name Resource::GetResourceID() {
		return ResourceID;
	}

}

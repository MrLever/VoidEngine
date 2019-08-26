//STD Headers

//Library Headers

//Void Engine Headers
#include "Resource.h"

namespace EngineUtils {
	///Public Functions
	Resource::Resource(const std::string& filePath) 
		: ResourceID(filePath), ResourcePath(filePath) {
		ResourceValid = std::filesystem::exists(ResourcePath);
	}

	Resource::~Resource() {

	}

	bool Resource::GetResourceValid() {
		return ResourceValid;
	}

	Name Resource::GetResourceID() {
		return ResourceID;
	}

}

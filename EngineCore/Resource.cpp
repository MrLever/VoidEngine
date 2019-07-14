//STD Headers

//Library Headers

//Void Engine Headers
#include "Resource.h"

namespace EngineUtils {
	///Public Functions
	Resource::Resource(const std::string& filePath) 
		: ResourceID(filePath), ResourcePath(filePath), LoadComplete(false) {
		ResourceValid = std::filesystem::exists(ResourcePath);
	}

	Resource::~Resource() {

	}

	UUID Resource::GetResourceID() {
		return ResourceID;
	}

	bool Resource::GetLoadComplete() {
		return LoadComplete;
	}
}

//STD Headers

//Library Headers

//Void Engine Headers
#include "Resource.h"

namespace utils {
	///Public Functions
	Resource::Resource(const std::string& filePath) 
		: ResourceID(filePath), ResourcePath(filePath), IsComposite(false), IsInitialized(false), IsThreadSafe(false) {
		
		ResourceValid = std::filesystem::exists(ResourcePath);
	}

	Resource::~Resource() {

	}

	void Resource::LoadComposite(ResourceManager* manager) {
		;
	}

	bool Resource::GetResourceValid() {
		return ResourceValid;
	}

	Name Resource::GetResourceID() {
		return ResourceID;
	}

}

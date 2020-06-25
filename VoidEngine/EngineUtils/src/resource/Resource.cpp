//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/resource/Resource.h"

namespace utils {
	///Public Functions
	Resource::Resource(const std::string& filePath) 
		: m_ResourceID(filePath), m_ResourcePath(filePath), m_IsInitialized(false){
		
		m_ResourceValid = std::filesystem::exists(m_ResourcePath);
		if (!m_ResourceValid) {
			utils::Logger::LogWarning("Resource located at [" + filePath + "] not found");
		}
	}

	Resource::~Resource() {

	}

	void Resource::LoadDependentResource(const std::string& type, const std::string& location) {
		VE_ASSERT(false, "NYI");
		//FactoryBase<Resource>::Create(type, location);
	}

	bool Resource::IsValid() {
		return m_ResourceValid;
	}

	bool Resource::GetIsInitialized() {
		return m_IsInitialized;
	}

	Name Resource::GetResourceID() {
		return m_ResourceID;
	}

}

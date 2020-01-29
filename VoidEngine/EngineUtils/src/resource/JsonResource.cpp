//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/resource/JsonResource.h"

namespace utils {

	JsonResource::JsonResource(const std::string& filePath) : Resource(filePath) {
	
	}

	bool JsonResource::Load() {
		std::ifstream configFile(ResourcePath);

		if (!configFile.is_open()) {
			return LoadErrorResource();
		}

		configFile >> Data;
		return true;
	}

	bool JsonResource::LoadErrorResource() {
		Data["Error"] = true;

		return false;
	}

	void JsonResource::Initialize() {
		;
	}

}
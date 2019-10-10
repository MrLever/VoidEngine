//STD Headers

//Library Headers

//Void Engine Headers
#include "Model.h"

namespace core {
	Model::Model(const std::string& filePath) : utils::Resource(filePath) {
		TextureCache = nullptr;
		IsThreadSafe = false;
		IsComposite = true;
	}

	bool Model::Load() {
		return false;
	}

	bool Model::LoadErrorResource() {
		return false;
	}

	void Model::Initialize() {
	
	}
}
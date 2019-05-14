//STD Headers
#include <utility>

//Library Headers

//Coati headers
#include "Serializable.h"

namespace EngineCore {

	Serializable::Serializable(std::string targetFilePath) : FilePath(std::move(targetFilePath)) {

	}

	Serializable::~Serializable() {

	}

}
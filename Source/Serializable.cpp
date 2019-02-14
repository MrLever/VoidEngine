#include "Serializable.h"

Serializable::Serializable(std::string targetFilePath) : FilePath(targetFilePath) {
	Load();
}

Serializable::~Serializable() {
	Save();
}

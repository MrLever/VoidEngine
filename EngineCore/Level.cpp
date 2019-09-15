//STD Headers


//Library Headers


//Coati Headers
#include "Level.h"

namespace EngineCore {

	Level::Level() : LevelName("Error") {

	}

	Level::~Level() {

	}

	EngineUtils::Name Level::GetName() {
		return LevelName;
	}

}
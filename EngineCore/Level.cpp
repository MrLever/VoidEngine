//STD Headers


//Library Headers


//Coati Headers
#include "Level.h"

namespace EngineCore {

	Level::Level(int ID) {

		levelID = ID;

	}


	Level::~Level() {



	}

	int Level::GetName() const {

		return levelID;

	}

	void Level::Tick() {


	}

}
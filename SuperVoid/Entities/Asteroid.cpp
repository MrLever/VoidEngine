//STD Headers

//External Headers

//SuperVoid Headers
#include "Asteroid.h"

namespace SuperVoid {
	TYPE_INFO_IMPL(Asteroid)

	ENABLE_FACTORY(Asteroid, core::Entity)

	Asteroid::Asteroid() : Entity() {
	
	}


}
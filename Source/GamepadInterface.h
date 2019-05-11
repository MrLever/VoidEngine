#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "GenericInputObject.h"
#include "GamepadInput.h"

namespace EngineCore {

	class GamepadInterface : public GenericInputObject<GamepadInput> {

	public:
		GamepadInterface(int ID);
		~GamepadInterface();

	};

}
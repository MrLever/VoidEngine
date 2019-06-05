#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "GenericInputInterface.h"
#include "GamepadInput.h"

namespace EngineCore {

	class GamepadInterface : public GenericInputInterface {

	public:
		GamepadInterface(int ID);
		~GamepadInterface();

	};

}
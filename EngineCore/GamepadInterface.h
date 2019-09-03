#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "InputInterface.h"
#include "GamepadInput.h"

namespace EngineCore {

	/**
	 * @class MouseInterface
	 * @brief Provides extra interface functionalities for handling joystick 
	 *        and analog trigger inputs
	 */
	class GamepadInterface : public InputInterface<GamepadInput>{
	public:
		GamepadInterface() = default;
		~GamepadInterface() = default;
	};

}
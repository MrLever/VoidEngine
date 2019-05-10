#pragma once
//STD Headers
#include <vector>

//Library Headers

//Coati Headers
#include "KeyboardInterface.h"
#include "MouseInterface.h"
#include "GamepadInterface.h"

namespace EngineCore {

	class InputInterface {
		//Forward class Definitions

	public:
		//Public Class members

	private:
		//Private Class Members
		KeyboardInterface Keyboard;
		MouseInterface Mouse;
		GamepadInterface Gamepad;

	public:
		InputInterface();
		~InputInterface();
	};

}
#pragma once
//STD Headers
#include <vector>
#include <memory>

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
		//tors
		InputInterface();
		~InputInterface();

	private:

	public:
		//Public Member Functions
		std::shared_ptr<KeyboardInterface> GetKeyboardInterface();
		std::shared_ptr<MouseInterface> GetMouseInterface();
	};

}
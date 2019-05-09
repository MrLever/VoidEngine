#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "KeyboardInterface.h"
#include "MouseInterface.h"

namespace EngineCore {

	class InputInterface {
		//Forward class Definitions

	public:
		//Public Class members

	private:
		//Private Class Members
		KeyboardInterface Keyboard;
		MouseInterface Mouse;

	public:
		InputInterface();
		~InputInterface();
	};

}
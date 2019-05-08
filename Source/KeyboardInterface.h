#pragma once
//STD Headers
#include <queue>

//Library Headers

//Coati Headers
#include "KeyboardInput.h"

namespace EngineCore {

	class KeyboardInterface {
	private:
		//Private Class Members
		std::queue<KeyboardInput> Events;

	public:
		//tors
		KeyboardInterface();
		~KeyboardInterface();
	
	private:
		//private member functions
	
	public:
		//public member functions
		std::queue<KeyboardInput> Poll();

	};

}
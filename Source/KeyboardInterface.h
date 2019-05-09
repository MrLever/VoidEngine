#pragma once
//STD Headers
#include <queue>

//Library Headers

//Coati Headers
#include "GenericInputObject.h"
#include "KeyboardInput.h"

namespace EngineCore {

	class KeyboardInterface : GenericInputObject<KeyboardInput>{
	private:
		//Private Class Members
		std::queue<KeyboardInput> Events;

	public:
		//tors
		KeyboardInterface(int ID);
		~KeyboardInterface();
	
	private:
		//private member functions
	
	public:
		//public member functions


	};

}
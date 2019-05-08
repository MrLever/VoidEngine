//STD Headers

//Library Headers

//Coati Headers
#include "KeyboardInterface.h"


namespace EngineCore {

	//tors
	KeyboardInterface::KeyboardInterface() {

	}

	KeyboardInterface::~KeyboardInterface() {

	}

	

	//Private Member Functions


	//Public Member Functions
	std::queue<KeyboardInput> KeyboardInterface::Poll() {
		//Take snapshot of input event queue
		auto res = Events;

		//Clear queue
		Events = std::queue<KeyboardInput>();
		
		//Return snapshot
		return res;
	}
}
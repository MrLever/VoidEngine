//STD Headers

//Library Headers

//Coati Headers
#include "MouseInterface.h"


namespace EngineCore {

	//Tors
	MouseInterface::MouseInterface(int ID) : GenericInputInterface(ID) {
		MouseXPos = 0;
		MouseYPos = 0;
	}


	MouseInterface::~MouseInterface() {
	}

	//Private Member Functions

	//Public Member Functions
	void MouseInterface::UpdateMousePosition(double xPos, double yPos) {
		MouseXPos = xPos;
		MouseYPos = yPos;
	}
}
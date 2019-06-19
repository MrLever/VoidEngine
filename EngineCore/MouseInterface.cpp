//STD Headers

//Library Headers

//Coati Headers
#include "MouseInterface.h"


namespace EngineCore {

	//Tors
	MouseInterface::MouseInterface(int ID) : GenericInputInterface(ID) {
	}


	MouseInterface::~MouseInterface() {
	}

	//Private Member Functions

	//Public Member Functions
	void MouseInterface::UpdateMousePosition(double xPos, double yPos) {
		Position.X = xPos;
		Position.Y = yPos;
	}
}
//STD Headers

//Library Headers

//Coati Headers
#include "MouseInterface.h"


namespace EngineCore {
	//Public Member Functions
	void MouseInterface::UpdateMousePosition(double xPos, double yPos) {
		Position.X = xPos;
		Position.Y = yPos;
	}
}
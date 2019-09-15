//STD Headers

//Library Headers

//Coati Headers
#include "MouseInterface.h"


namespace EngineCore {
	//Public Member Functions
	void MouseInterface::UpdateMousePosition(float xPos, float yPos) {
		CursorPosition.X = xPos;
		CursorPosition.Y = yPos;
	}

	void MouseInterface::ReportScrollAction(double delta) {
		ScrollOffset += delta;
	}

	EngineMath::Vector2 MouseInterface::PollCursorPosition(){
		return CursorPosition;
	}
	
	double MouseInterface::PollScrollOffset() {
		auto res = ScrollOffset;
		
		//Reset offset after polling
		ScrollOffset = 0;

		return res;
	}
}
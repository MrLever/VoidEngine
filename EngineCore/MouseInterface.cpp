//STD Headers

//Library Headers

//Coati Headers
#include "MouseInterface.h"


namespace EngineCore {
	//Public Member Functions
	void MouseInterface::UpdateMousePosition(double xPos, double yPos) {
		CursorPosition.X = xPos;
		CursorPosition.Y = yPos;
	}

	void MouseInterface::ReportScrollAction(int delta) {
		ScrollOffset += delta;
	}

	EngineMath::Vector2<double> MouseInterface::PollCursorPosition(){
		return CursorPosition;
	}
	
	int MouseInterface::PollScrollOffset() {
		auto res = ScrollOffset;
		
		//Reset offset after polling
		ScrollOffset = 0;

		return res;
	}
}
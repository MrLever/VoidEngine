#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "MouseInput.h"
#include "GenericInputInterface.h"

namespace EngineCore {

	class MouseInterface : public GenericInputInterface<MouseInput, MouseButton> {
	
	private:
		//Private Class Members
		double MouseXPos;
		double MouseYPos;

	public:
		MouseInterface(int ID);
		~MouseInterface();
	
	private:
		//Private Member Functions

	public:
		//Public Member Functions
		void UpdateMousePosition(double xPos, double yPos);
	};

}
#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "MouseInput.h"
#include "GenericInputInterface.h"
#include "Vector.h"

namespace EngineCore {

	class MouseInterface : public GenericInputInterface{
	
	private:
		//Private Class Members
		EngineMath::Vector2<double> Position;

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
#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "MouseInput.h"
#include "GenericInputObject.h"

namespace EngineCore {

	class MouseInterface : GenericInputObject<MouseInput> {
	
	private:
		//Private Class Members

	public:
		MouseInterface(int ID);
		~MouseInterface();
	
	private:
		//Private Member Functions

	public:
		//Public Member Functions
	};

}
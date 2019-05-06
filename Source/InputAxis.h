#pragma once
//STD Headers
#include <unordered_map>
#include <stack>

//Library Headers

//Coati Headesr
#include "KeyboardInput.h"

namespace EngineCore {

	class InputAxis	{

	private:
		double AxisValue;
		std::unordered_map<KeyType, double> AxisBindings;

	public:
		InputAxis();
		~InputAxis();
	
	private:

	public:
		void AddBinding(KeyType input, double scale);

		void UpdateAxis(const KeyboardInput &input);
		void Reset();
		
		double Poll() const;
	};

}
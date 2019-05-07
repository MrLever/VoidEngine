#pragma once
//STD Headers
#include <unordered_map>
#include <stack>
#include <list>
//Library Headers

//Coati Headesr
#include "KeyboardInput.h"

namespace EngineCore {

	class InputAxis	{

	private:
		double AxisValue;
		std::unordered_map<KeyType, double> AxisBindings;
		std::list<KeyType> CommandQueue;

	public:
		InputAxis();
		~InputAxis();
	
	private:
		void TriggerBinding(const EngineCore::KeyboardInput& input);
		void ReleaseBinding(const EngineCore::KeyboardInput& input);

	public:
		void AddBinding(KeyType input, double scale);

		

		void UpdateAxis(const KeyboardInput &input);
		void Reset();
		
		double Poll() const;
	};

}
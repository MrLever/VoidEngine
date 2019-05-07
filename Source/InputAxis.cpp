//STD Headers

//Library Headers


//Coati Headers
#include "InputAxis.h"


namespace EngineCore {

	InputAxis::InputAxis(){
		AxisValue = 0;
	}


	InputAxis::~InputAxis()	{

	}
	
	//Private Member functions
	void InputAxis::ReleaseBinding(const EngineCore::KeyboardInput& input)
	{
		//Remove all instances of key being released in the command queue.
		for (auto it = CommandQueue.begin(); it != CommandQueue.end(); ) {
			if (*it == input.GetKey()) {
				it = CommandQueue.erase(it);
			}
			else {
				++it;
			}
		}

		//If the command queue is not empty, apply the first command in the queue
		//Else reset the axis.
		if (!CommandQueue.empty()) {
			AxisValue = AxisBindings[CommandQueue.front()];
		}
		else {
			Reset();
		}
	}

	void InputAxis::TriggerBinding(const EngineCore::KeyboardInput& input) {
		AxisValue = AxisBindings[input.GetKey()];
		CommandQueue.push_back(input.GetKey());
	}


	//Public Member Functions
	void InputAxis::AddBinding(KeyType input, double scale) {
		AxisBindings[input] = scale;
	}

	void InputAxis::UpdateAxis(const KeyboardInput &input)	{
		if (input.GetKeyState() == KeyState::Held) {
			return;
		}
		if (AxisBindings.find(input.GetKey()) == AxisBindings.end()) {
			return;
		}

		if (input.GetKeyState() == KeyState::Pressed) {
			TriggerBinding(input);
		}
		else if(input.GetKeyState() == KeyState::Released) {
			ReleaseBinding(input);
		}
	}

	void InputAxis::Reset() {
		AxisValue = 0;
		CommandQueue.erase(CommandQueue.begin(), CommandQueue.end());
	}

	double InputAxis::Poll() const {
		return AxisValue;
	}

}
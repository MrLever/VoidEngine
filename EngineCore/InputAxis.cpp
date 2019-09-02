//STD Headers
#include <utility>

//Library Headers


//Coati Headers
#include "InputAxis.h"

namespace EngineCore {

	InputAxis::InputAxis(std::string axisName) : AxisName(axisName){
		AxisValue = 0;
	}

	InputAxis::~InputAxis()	{
		Reset();
	}

	bool InputAxis::operator==(const InputAxis& other){
		return this->AxisName == other.AxisName;
	}
	
	//Private Member functions
	void InputAxis::ReleaseBinding(const KeyboardInput& input)
	{
		//Remove all instances of key being released in the command queue.
		for (auto it = CommandQueue.begin(); it != CommandQueue.end(); ) {
			if (*it == input.GetButton()) {
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

	void InputAxis::TriggerBinding(const KeyboardInput& input) {
		AxisValue = AxisBindings[input.GetButton()];
		CommandQueue.push_back(input.GetButton());
	}


	//Public Member Functions
	void InputAxis::AddBinding(KeyboardButton input, double scale) {
		AxisBindings[input] = scale;
	}

	EngineUtils::Name InputAxis::GetName() const{
		return AxisName;
	}

	void InputAxis::UpdateAxis(const KeyboardInput& input)	{
		if (input.GetButtonState() == ButtonState::Held) {
			return;
		}
		if (AxisBindings.find(input.GetButton()) == AxisBindings.end()) {
			return;
		}

		if (input.GetButtonState() == ButtonState::Pressed) {
			TriggerBinding(input);
		}
		else if(input.GetButtonState() == ButtonState::Released) {
			ReleaseBinding(input);
		}
	}

	void InputAxis::Reset() {
		AxisValue = 0;
		if (!CommandQueue.empty()) {
			CommandQueue.erase(CommandQueue.begin(), CommandQueue.end());
		}
	}

	double InputAxis::Poll() const {
		return AxisValue;
	}

}
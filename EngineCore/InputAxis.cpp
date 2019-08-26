//STD Headers
#include <utility>

//Library Headers


//Coati Headers
#include "InputAxis.h"

namespace EngineCore {

	InputAxis::InputAxis(std::string axisName) : AxisName(axisName), AxisID(axisName){
		AxisValue = 0;
	}

	InputAxis::~InputAxis()	{
		Reset();
	}

	bool InputAxis::operator==(const InputAxis& other){
		return this->AxisID == other.AxisID;
	}
	
	//Private Member functions
	void InputAxis::ReleaseBinding(const KeyboardInputPtr input)
	{
		//Remove all instances of key being released in the command queue.
		for (auto it = CommandQueue.begin(); it != CommandQueue.end(); ) {
			if (*it == input->GetButton<KeyboardButton>()) {
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

	void InputAxis::TriggerBinding(const EngineCore::KeyboardInputPtr input) {
		AxisValue = AxisBindings[input->GetButton<KeyboardButton>()];
		CommandQueue.push_back(input->GetButton<KeyboardButton>());
	}


	//Public Member Functions
	void InputAxis::AddBinding(KeyboardButton input, double scale) {
		AxisBindings[input] = scale;
	}

	EngineUtils::Name InputAxis::GetID() const{
		return AxisID;
	}

	void InputAxis::UpdateAxis(const KeyboardInputPtr input)	{
		if (input->GetButtonState() == ButtonState::Held) {
			return;
		}
		if (AxisBindings.find(input->GetButton<KeyboardButton>()) == AxisBindings.end()) {
			return;
		}

		if (input->GetButtonState() == ButtonState::Pressed) {
			TriggerBinding(input);
		}
		else if(input->GetButtonState() == ButtonState::Released) {
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
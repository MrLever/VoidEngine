//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/GamepadButtonEvent.h"

namespace core {

	GamepadButtonEvent::GamepadButtonEvent(const GamepadInput& input): Input(std::move(input)) {

	}

}
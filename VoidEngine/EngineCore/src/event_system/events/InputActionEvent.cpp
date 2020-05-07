//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/InputActionEvent.h"

namespace core {

	TYPE_INFO_IMPL(InputActionEvent)

	InputActionEvent::InputActionEvent(InputAction& action) : action(action) {

	}

}

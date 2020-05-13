#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "core\platform\Platform.h"


namespace platform {
	std::shared_ptr<core::Window> platform::MakeWindow(core::EventSystem* bus, core::WindowData& data) {
		return std::make_shared<WindowsWindow>(bus, data);
	}
}
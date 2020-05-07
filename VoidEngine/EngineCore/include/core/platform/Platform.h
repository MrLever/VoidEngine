#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "core/platform/windowing/WindowsWindow.h"

namespace platform {
	/**
	 * Factory method to construct Window interface appropriate to the current operating system
	 * @param bus The event bus to connect to the window
	 * @param data The window data to use during initialization
	 */
	std::shared_ptr<core::Window> MakeWindow(core::EventSystem* bus, core::WindowData& data);
}
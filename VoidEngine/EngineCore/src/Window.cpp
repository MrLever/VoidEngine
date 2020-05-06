//STD Headers
#include <iostream>

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "Window.h"
#include "event_system/events/AxisInputEvent.h"
#include "event_system/events/WindowClosedEvent.h"
#include "event_system/events/WindowResizedEvent.h"
#include "event_system/events/MouseButtonEvent.h"
#include "event_system/events/PauseGameEvent.h"
#include "event_system/events/MouseMovedEvent.h"
#include "event_system/events/KeyboardButtonEvent.h"
#include "event_system/events/GamepadButtonEvent.h"
#include "input/definitions/AxisInput.h"
#include "input/definitions/GamepadInput.h"
#include "rendering/Renderer.h"

namespace core {
	Window::Window(EventSystem* eventSystem, WindowData& data) 
		: EventListener(eventSystem), m_Viewport(0, 0, data.windowWidth, data.windowHeight) {
		
		m_WindowText = data.gameName;
		SubscribeToEvent<PauseGameEvent>(
			[this](PauseGameEvent* event) {
				ToggleCursorCapture();
			}
		);
	}

	Window::~Window() {

	}

	void Window::SetWindowSize(int width, int height) {
		m_Viewport = Viewport(0, 0, width, height);
		PostEvent<WindowResizedEvent>(width, height);
	}

	Viewport Window::GetViewport() const {
		return m_Viewport;
	}

}
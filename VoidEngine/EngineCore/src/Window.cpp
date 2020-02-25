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
#include "rendering/Components/CameraComponent.h"

namespace core {

	Window::Window(EventBus* bus, WindowData& data) : EventBusNode(bus), DeviceContext(nullptr) {
		WindowWidth = data.windowWidth;
		WindowHeight = data.windowHeight;
		GameName = data.gameName;
	}


	Window::~Window() {

	}

	void Window::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<PauseGameEvent>(
			[this](PauseGameEvent* event) {
				ToggleCursorCapture();
			}
		);
	}

	unsigned Window::GetSubscription() {
		return 
			static_cast<unsigned>(EventCategory::WINDOW) |
			static_cast<unsigned>(EventCategory::GAMEPLAY);
	}

	void Window::SetWindowSize(int width, int height) {
		WindowWidth = width;
		WindowHeight = height;
		DeviceContext->SetViewport(0, 0, width, height);
		PublishEvent(new WindowResizedEvent(width, height));
	}

	int Window::GetWindowWidth() const {
		return WindowWidth;
	}

	int Window::GetWindowHeight() const {
		return WindowHeight;
	}

	std::shared_ptr<RenderingContext> Window::GetRenderingContext() {
		return DeviceContext;
	}

}
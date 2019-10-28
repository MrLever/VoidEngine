//STD Headers
#include <memory>
#include <utility>

//Library Headers

//Void Engine Headers
#include "InputManager.h"
#include "AxisInput.h"
#include "EventBus.h"
#include "MouseButtonEvent.h"
#include "MouseMovedEvent.h"
#include "PauseGameEvent.h"
#include "Level.h"

namespace core {

	InputManager::InputManager(
		EventBus* bus, 
		const utils::ResourceHandle<utils::Configuration>& configuration,
		std::shared_ptr<utils::ThreadPool> threadPool
		) : EventBusNode(bus), Configurable(configuration), ControlLayoutCache(threadPool), JoystickDeadzone(0) {
		
		Configure();
	}

	void InputManager::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<KeyboardInputEvent>(
			[this](KeyboardInputEvent* event) {
				ReportInput(event->Input);
			}
		);

		dispatcher.Dispatch<MouseButtonEvent>(
			[this](MouseButtonEvent* event) {
				ReportInput(event->Input);
			}
		);

		dispatcher.Dispatch<MouseMovedEvent>(
			[this](MouseMovedEvent* event) {
				static double MouseXPrev = -1.0f;
				static double MouseYPrev = -1.0f;
				static float SENSITIVITY = 0.05f;
				
				if (MouseXPrev == -1.0f || MouseYPrev == 1.0f) {
					MouseXPrev = float(event->Position.X);
					MouseYPrev = float(event->Position.Y);
				}

				//Convert raw data into AxisInputs
				AxisInput MouseX(RawAxisType::MOUSE_X, (float)(event->Position.X - MouseXPrev) * SENSITIVITY);
				AxisInput MouseY(RawAxisType::MOUSE_Y, (float)(MouseYPrev - event->Position.Y) * SENSITIVITY);
				
				//Report AxisInputs to input manager
				ReportInput(MouseX);
				ReportInput(MouseY);

				MouseXPrev = event->Position.X;
				MouseYPrev = event->Position.Y;
			}
		);
	}

	unsigned InputManager::GetSubscription() {
		return static_cast<unsigned>(EventCategory::RAW_INPUT);
	}

	void InputManager::ProcessInput(Level* scene, float deltaTime) {
		auto entities = scene->GetScene();

		//Dispatch Actions
		while (!InputActionBuffer.empty()) {
			for (auto& entity : entities) {
				entity->Input(InputActionBuffer.front(), deltaTime);
			}
			InputActionBuffer.pop_front();
		}

		//Dispatch Axis Updates
		while (!AxisUpdateBuffer.empty()) {
			auto axisInput = AxisUpdateBuffer.front();
			AxisUpdateBuffer.pop_front();

			if (std::abs(axisInput.Value) < JoystickDeadzone) {
				continue;
			}

			for (auto& entity : entities) {
				entity->Input(axisInput, deltaTime);
			}
		}
	}

	void InputManager::Configure() {
		auto configuration = Config.GetResource();
		DefaultControls = ControlLayoutCache.GetResource(
			configuration->GetAttribute<std::string>("defaultControls")
		);
		ActiveControls = DefaultControls;

		DefaultControls->Initialize();

		JoystickDeadzone = configuration->GetAttribute<float>("joystickDeadzone");
	}

}
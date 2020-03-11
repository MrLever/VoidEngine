//STD Headers
#include <memory>
#include <utility>

//Library Headers

//Void Engine Headers
#include "Level.h"

#include "event_system/EventBus.h"
#include "event_system/events/MouseButtonEvent.h"
#include "event_system/events/MouseMovedEvent.h"
#include "event_system/events/PauseGameEvent.h"
#include "event_system/events/GamepadButtonEvent.h"
#include "event_system/events/AxisInputEvent.h"
#include "event_system/events/InputActionEvent.h"
#include "input/InputManager.h"
#include "input/definitions/AxisInput.h"

namespace core {

	InputManager::InputManager(
		EventBus* bus, 
		const utils::ResourceHandle<utils::Configuration>& configuration
	) : EventBusNode(bus), Configurable(configuration), JoystickDeadzone(0) {
		
		Configure();
	}

	void InputManager::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<KeyboardButtonEvent>(
			[this](KeyboardButtonEvent* event) {
				CaptureInput(event->Input);
			}
		);

		dispatcher.Dispatch<MouseButtonEvent>(
			[this](MouseButtonEvent* event) {
				CaptureInput(event->Input);
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
				CaptureInput(MouseX);
				CaptureInput(MouseY);

				MouseXPrev = event->Position.X;
				MouseYPrev = event->Position.Y;
			}
		);

		dispatcher.Dispatch<GamepadButtonEvent>(
			[this](GamepadButtonEvent* event) {
				CaptureInput(event->Input);
			}
		);

		dispatcher.Dispatch<AxisInputEvent>(
			[this](AxisInputEvent* event) {
				CaptureInput(event->Input);
			}
		);
	}

	unsigned InputManager::GetSubscription() {
		return static_cast<unsigned>(EventCategory::RAW_INPUT);
	}


	void InputManager::Configure() {
		auto configuration = Config.GetResource();
		m_DefaultControls = m_ControlLayoutCache.GetResource(
			configuration->GetAttribute<std::string>("defaultControls")
		);
		m_ActiveControls = m_DefaultControls;

		m_DefaultControls->Initialize();

		JoystickDeadzone = configuration->GetAttribute<float>("joystickDeadzone");
	}

	void InputManager::ProcessInput(std::vector<Entity*>& entities, float deltaTime) {
		ProcessInputActions(entities, deltaTime);
		ProcessAxisUpdates(entities, deltaTime);
	}

	void InputManager::SetActiveInputMapping(const std::string& profilePath) {
		m_ActiveControls = m_ControlLayoutCache.GetResource(profilePath);
		m_ActiveControls->Initialize();
	}

	void InputManager::ProcessInputActions(std::vector<Entity*>& entities, float deltaTime) {
		while (!m_InputActionBuffer.empty()) {
			auto inputAction = m_InputActionBuffer.front();
			for (auto& entity : entities) {
				entity->Input(inputAction, deltaTime);
			}

			PublishEvent(new InputActionEvent(inputAction));
			m_InputActionBuffer.pop_front();
		}
	}

	void InputManager::ProcessAxisUpdates(std::vector<Entity*>& entities, float deltaTime) {
		auto defaultControlAxisReadings = m_DefaultControls->PollAxes();
		auto activeControlAxisReadings = m_ActiveControls->PollAxes();

		//Get any relevant axis updates
		m_AxisUpdateBuffer.insert(m_AxisUpdateBuffer.end(), defaultControlAxisReadings.begin(), defaultControlAxisReadings.end());
		m_AxisUpdateBuffer.insert(m_AxisUpdateBuffer.end(), activeControlAxisReadings.begin(), activeControlAxisReadings.end());

		//Dispatch Axis Updates
		while (!m_AxisUpdateBuffer.empty()) {
			auto axisInput = m_AxisUpdateBuffer.front();
			m_AxisUpdateBuffer.pop_front();

			if (std::abs(axisInput.Value) < JoystickDeadzone) {
				continue;
			}

			for (auto& entity : entities) {
				entity->Input(axisInput, deltaTime);
			}
		}
	}
}
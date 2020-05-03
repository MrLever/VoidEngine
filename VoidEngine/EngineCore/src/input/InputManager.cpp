//STD Headers
#include <memory>
#include <utility>

//Library Headers

//Void Engine Headers
#include "Level.h"

#include "event_system/EventSystem.h"
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
		EventSystem* eventSystem,
		const utils::ResourceHandle<utils::Configuration>& configuration
	) : EventListener(eventSystem), Configurable(configuration), joystickDeadzone(0) {
		
		Configure();

		SubscribeToEvent<KeyboardButtonEvent>(
			[this](KeyboardButtonEvent* event) {
				CaptureInput(event->input);
			}
		);

		SubscribeToEvent<MouseButtonEvent>(
			[this](MouseButtonEvent* event) {
				CaptureInput(event->Input);
			}
		);

		SubscribeToEvent<MouseMovedEvent>(
			[this](MouseMovedEvent* event) {
				static double MouseXPrev = -1.0f;
				static double MouseYPrev = -1.0f;
				static float SENSITIVITY = 0.05f;

				if (MouseXPrev == -1.0f || MouseYPrev == 1.0f) {
					MouseXPrev = float(event->position.X);
					MouseYPrev = float(event->position.Y);
				}

				//Convert raw data into AxisInputs
				AxisInput MouseX(RawAxisType::MOUSE_X, (float)(event->position.X - MouseXPrev) * SENSITIVITY);
				AxisInput MouseY(RawAxisType::MOUSE_Y, (float)(MouseYPrev - event->position.Y) * SENSITIVITY);

				//Report AxisInputs to input manager
				CaptureInput(MouseX);
				CaptureInput(MouseY);

				MouseXPrev = event->position.X;
				MouseYPrev = event->position.Y;
			}
		);

		SubscribeToEvent<MouseMovedEvent>(
			[this](MouseMovedEvent* event) {
				static double MouseXPrev = -1.0f;
				static double MouseYPrev = -1.0f;
				static float SENSITIVITY = 0.05f;

				if (MouseXPrev == -1.0f || MouseYPrev == 1.0f) {
					MouseXPrev = float(event->position.X);
					MouseYPrev = float(event->position.Y);
				}

				//Convert raw data into AxisInputs
				AxisInput MouseX(RawAxisType::MOUSE_X, (float)(event->position.X - MouseXPrev) * SENSITIVITY);
				AxisInput MouseY(RawAxisType::MOUSE_Y, (float)(MouseYPrev - event->position.Y) * SENSITIVITY);

				//Report AxisInputs to input manager
				CaptureInput(MouseX);
				CaptureInput(MouseY);

				MouseXPrev = event->position.X;
				MouseYPrev = event->position.Y;
			}
		);

		SubscribeToEvent<GamepadButtonEvent>(
			[this](GamepadButtonEvent* event) {
				CaptureInput(event->Input);
			}
		);

		SubscribeToEvent<AxisInputEvent>(
			[this](AxisInputEvent* event) {
				CaptureInput(event->Input);
			}
		);

	}

	void InputManager::Configure() {
		auto configuration = Config.GetResource();
		defaultControls = controlLayoutCache.GetResource(
			configuration->GetAttribute<std::string>("defaultControls")
		);
		activeControls = defaultControls;

		defaultControls->Initialize();

		joystickDeadzone = configuration->GetAttribute<float>("joystickDeadzone");
	}

	void InputManager::ProcessInput(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
		ProcessInputActions(entities, deltaTime);
		ProcessAxisUpdates(entities, deltaTime);
	}

	void InputManager::SetActiveInputMapping(const std::string& profilePath) {
		activeControls = controlLayoutCache.GetResource(profilePath);
		activeControls->Initialize();
	}

	void InputManager::ProcessInputActions(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
		while (!inputActionBuffer.empty()) {
			auto inputAction = inputActionBuffer.front();
			for (auto& entity : entities) {
				entity->Input(inputAction, deltaTime);
			}

			PostEvent(new InputActionEvent(inputAction));
			inputActionBuffer.pop_front();
		}

		inputActionBuffer = {};
	}

	void InputManager::ProcessAxisUpdates(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
		auto defaultControlAxisReadings = defaultControls->PollAxes();
		auto activeControlAxisReadings = activeControls->PollAxes();

		//Get any relevant axis updates
		axisUpdateBuffer.insert(axisUpdateBuffer.end(), defaultControlAxisReadings.begin(), defaultControlAxisReadings.end());
		axisUpdateBuffer.insert(axisUpdateBuffer.end(), activeControlAxisReadings.begin(), activeControlAxisReadings.end());

		//Dispatch Axis Updates
		while (!axisUpdateBuffer.empty()) {
			auto axisInput = axisUpdateBuffer.front();
			axisUpdateBuffer.pop_front();

			if (std::abs(axisInput.Value) < joystickDeadzone) {
				continue;
			}

			for (auto& entity : entities) {
				entity->Input(axisInput, deltaTime);
			}
		}

		axisUpdateBuffer = {};
	}
}
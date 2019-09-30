//STD Headers
#include <memory>
#include <iostream>
#include <utility>

//Library Headers

//Void Engine Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace core {

	InputManager::InputManager(
			ThreadPoolPtr threadPool,
			ResourceManagerPtr resourceManager, const EngineUtils::ResourceHandle& configuration
		) : Configurable(configuration), GameThreadPool(std::move(threadPool)), 
		    GameResourceManager(std::move(resourceManager)) {
		
		Configure();
	}

	void InputManager::ReportInput(const KeyboardInput& input) {
		KeyboardInputBuffer.push_back(input);
	}

	void InputManager::ReportInput(const MouseInput& input) {
		MouseInputBuffer.push_back(input);
	}

	void InputManager::ReportInput(const GamepadInput& input) {
		GamepadInputBuffer.push_back(input);
	}

	void InputManager::ReportInput(const InputAxis& input){
		InputAxisDataBuffer.push_back(input);
	}

	void InputManager::ProcessInput(const std::vector<Entity*> scene, float deltaTime) {
		//Process Mouse Input
		while (!MouseInputBuffer.empty()) {
			auto button = MouseInputBuffer.front();

			std::string eventType;

			if (button.GetButton() == MouseButton::LEFT) {
				eventType = "Fire";
			}

			DispatchEvent(scene, InputEvent(eventType), deltaTime);

			MouseInputBuffer.pop_front();
		}

		//Process KB like mouse
		while (!KeyboardInputBuffer.empty()) {
			auto input = KeyboardInputBuffer.front();
			auto button = input.GetButton();

			std::string eventType;
			if (button == KeyboardButton::W) {
				InputAxisDataBuffer.push_back(
					InputAxis("UpAxis", 1.0f)
				);
			}
			else if (button == KeyboardButton::A) {
				InputAxisDataBuffer.push_back(
					InputAxis("RightAxis", -1.0f)
				);
			}
			else if (button == KeyboardButton::S) {
				InputAxisDataBuffer.push_back(
					InputAxis("UpAxis", -1.0f)
				);
			}
			else if (button == KeyboardButton::D) {
				InputAxisDataBuffer.push_back(
					InputAxis("RightAxis", 1.0f)
				);
			}

			DispatchEvent(scene, InputEvent(eventType), deltaTime);

			KeyboardInputBuffer.pop_front();
		}

		//Process Gamepad input
		while (!GamepadInputBuffer.empty()) {
			auto input = GamepadInputBuffer.front();
			auto button = input.GetButton();
			std::string eventType;

			if (button == GamepadButton::DPAD_UP) {
				InputAxisDataBuffer.push_back(
					InputAxis("UpAxis", 1.0f)
				);
			}
			else if (button == GamepadButton::DPAD_DOWN) {
				InputAxisDataBuffer.push_back(
					InputAxis("UpAxis", -1.0f)
				);
			}
			else if (button == GamepadButton::DPAD_LEFT) {
				InputAxisDataBuffer.push_back(
					InputAxis("RightAxis", -1.0f)
				);
			}
			else if (button == GamepadButton::DPAD_RIGHT) {
				InputAxisDataBuffer.push_back(
					InputAxis("RightAxis", 1.0f)
				);
			}

			DispatchEvent(scene, InputEvent(eventType), deltaTime);

			GamepadInputBuffer.pop_front();
		}

		while (!InputAxisDataBuffer.empty()) {
			auto axisReading = InputAxisDataBuffer.front();

			DispatchEvent(scene, axisReading, deltaTime);

			InputAxisDataBuffer.pop_front();
		}
	}

	void InputManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

	void InputManager::DispatchEvent(
			const std::vector<core::Entity*>& scene, 
			const InputEvent& event,
			float deltaTime
		) {
		static const EngineUtils::Name ERROR_EVENT_ID("Error");

		if (event.EventName == ERROR_EVENT_ID) {
			return;
		}

		for (auto& entity : scene) {
			entity->Input(event, deltaTime);
		}
	}

	void InputManager::DispatchEvent(
		const std::vector<core::Entity*>& scene,
		const InputAxis& axisData,
		float deltaTime
	) {
		static const EngineUtils::Name ERROR_EVENT_ID("Error");

		for (auto& entity : scene) {
			entity->Input(axisData, deltaTime);
		}
	}

}
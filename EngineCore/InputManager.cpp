//STD Headers
#include <memory>
#include <iostream>
#include <utility>

//Library Headers

//Void Engine Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace EngineCore {

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
			auto button = KeyboardInputBuffer.front();
			
			std::string eventType;
			if (button.GetButton() == KeyboardButton::W) {
				eventType = "Move Up";
			}
			else if (button.GetButton() == KeyboardButton::A) {
				eventType = "Move Left";
			}
			else if (button.GetButton() == KeyboardButton::S) {
				eventType = "Move Down";
			}
			else if (button.GetButton() == KeyboardButton::D) {
				eventType = "Move Right";
			}

			DispatchEvent(scene, InputEvent(eventType), deltaTime);

			KeyboardInputBuffer.pop_front();
		}

		//Process Gamepad like mouse
		while (!GamepadInputBuffer.empty()) {
			auto button = GamepadInputBuffer.front();

			GamepadInputBuffer.pop_front();
		}
	}

	void InputManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

	void InputManager::DispatchEvent(
			const std::vector<EngineCore::Entity*>& scene, 
			const EngineCore::InputEvent& event,
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

}
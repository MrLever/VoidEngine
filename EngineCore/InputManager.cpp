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

	void InputManager::ProcessInput(const std::vector<Entity*> scene) {
		//Process Mouse Input
		while (!MouseInputBuffer.empty()) {
			auto button = MouseInputBuffer.front();
			std::cout << "Mouse Button Pressed: " << static_cast<unsigned>(button.GetButton()) << "\n";

			//Convert button to event
			//Send event to entity

			/*for (auto& entity : scene) {
			entity->Input();
			}*/
			MouseInputBuffer.pop_front();
		}

		//Process KB like mouse
		while (!KeyboardInputBuffer.empty()) {
			auto button = KeyboardInputBuffer.front();
			std::cout << "Keyboard Button Pressed: " << static_cast<unsigned>(button.GetButton()) << "\n";

			KeyboardInputBuffer.pop_front();
		}

		//Process Gamepad like mouse
		while (!GamepadInputBuffer.empty()) {
			auto button = GamepadInputBuffer.front();
			std::cout << "Keyboard Button Pressed: " << static_cast<unsigned>(button.GetButton()) << "\n";

			GamepadInputBuffer.pop_front();
		}
	}

	void InputManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}
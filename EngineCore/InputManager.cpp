//STD Headers
#include <memory>
#include <iostream>
#include <utility>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace EngineCore {

	InputManager::InputManager(
			ThreadPoolPtr threadPool,
			ResourceManagerPtr resourceManager, const EngineUtils::ResourceHandle& configuration
		) : Configurable(configuration), GameThreadPool(std::move(threadPool)), 
		    GameResourceManager(std::move(resourceManager)) {

	}

	void InputManager::HandleInput() {
		HandleKeyboard();
		HandleMouse();
		HandleGamepad();
	}

	void InputManager::HandleKeyboard() {

	}

	void InputManager::HandleMouse() {

	}

	void InputManager::HandleGamepad() {

	}

	void InputManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}
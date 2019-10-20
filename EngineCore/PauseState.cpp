//STD Headers

//Library Headers

//Void Engine Headers
#include "PauseState.h"
#include "WindowManager.h"

namespace core {

	void PauseState::Enter() {
		utils::Logger::LogDebug("Game Paused");
		WindowManager::GetActiveWindow()->SetCursor(true);
	}

	void PauseState::Update(Level* currentLevel, float deltaTime) {
		;
	}

	void PauseState::Exit() {
		utils::Logger::LogDebug("Game Resumed");
		WindowManager::GetActiveWindow()->SetCursor(false);
	}

}
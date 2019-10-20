//STD Headers

//Library Headers

//Void Engine Headers
#include "RunningState.h"
#include "WindowManager.h"

namespace core {
	RunningState::RunningState(Game* owner) : GameState(owner) {

	}

	void RunningState::Enter() {
		utils::Logger::LogDebug("Game Running");
		WindowManager::GetActiveWindow()->SetCursor(false);
	}

	void RunningState::Update(Level* currentLevel, const float deltaTime) {
		currentLevel->Update(deltaTime);
	}

	void RunningState::Exit() {
		utils::Logger::LogDebug("Game Execution Halting");
	}
}
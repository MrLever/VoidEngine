//STD Headers

//Library Headers

//Void Engine Headers
#include "PauseState.h"

namespace core {

	void PauseState::Enter() {
		utils::Logger::LogDebug("Game Paused");
		
	}

	void PauseState::Update(float deltaTime) {
		;
	}

	void PauseState::Exit() {
		utils::Logger::LogDebug("Game Resumed");
	}

}
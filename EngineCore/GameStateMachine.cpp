//STD Headers

//Library Headers

//Void Engine Headers
#include "GameStateMachine.h"
#include "Game.h"
#include "GameState.h"

namespace core {
	GameStateMachine::GameStateMachine(Game* owner) : Owner(owner) {

	}

	void GameStateMachine::Update(Level* currLevel, const float deltaTime) {
		if (!StateMachine.empty()) {
			StateMachine.top()->Update(currLevel, deltaTime);
		}
		else {
			utils::Logger::LogWarning("StateMachine empty, cannot update");
		}
	}

	void GameStateMachine::PushState(std::unique_ptr<GameState> state) {
		state->Enter();
		StateMachine.push(std::move(state));
	}

	void GameStateMachine::PopState() {
		if (!StateMachine.empty()) {
			StateMachine.top()->Exit();
			StateMachine.pop();
		}
		else {
			utils::Logger::LogWarning("Error: Pop called on empty state machine");
		}
	}
}
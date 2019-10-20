//STD Headers
#include <utility>
#include <string>

//Library Headers


//Void Engine Headers
#include "Engine.h"

#include "AudioManager.h"
#include "Console.h"
#include "Configuration.h"
#include "Game.h"
#include "InputManager.h"
#include "MessageBus.h"
#include "Renderer.h"
#include "ResourceAllocator.h"
#include "RunningState.h"
#include "ThreadPool.h"
#include "WindowManager.h"
#include "Logger.h"

namespace core {

	Game::Game(const std::string& configFile) 
		: GameEngine(configFile), StateMachine(this) {
		FrameRate = 0;

		LevelCache = std::make_shared<utils::ResourceAllocator<Level>>(
			GameEngine.GetThreadPool()
		);

		//Set the current level to the default level
		SetLevel(GameEngine.GetDefaultLevel());

		StateMachine.PushState(
			std::make_unique<RunningState>(this)
		);

		//Start game loop
		ExecuteGameLoop();
	}

	Game::~Game() {

	}

	void Game::Update(float deltaTime) {
		if (deltaTime - 0.5f < std::numeric_limits<float>::epsilon()) {
			deltaTime = 0.5f;
		}

		UpdateFramerate(deltaTime);
		CurrentLevel->Update(deltaTime);
	}

	void Game::ProcessInput(float deltaTime) {
		GameEngine.PollInput();
		GameEngine.ProcessInput(CurrentLevel.get(), deltaTime);
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		while (GameEngine.GetIsRunning()) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<float> deltaSeconds = currentTime - previousTime;
			auto deltaTime = deltaSeconds.count();
			
			//Handle input
			ProcessInput(deltaTime);
			
			//Update the scene
			Update(deltaTime);
			
			//Draw the scene
			GameEngine.Render(CurrentLevel.get());

			//Update previous time
			previousTime = currentTime;
		}
	}

	void Game::UpdateFramerate(double timeSinceLastFrame) {
		const static int ONE_SECOND = 1000;
		static auto lastTime = utils::GetGameTime();
		static int numFrames = 0;

		auto currentTime = utils::GetGameTime();
		numFrames++;

		if (currentTime - lastTime >= ONE_SECOND) {
			GameEngine.GetThreadPool()->SubmitJob(
				[] (double frameTime){
					utils::Logger::LogInfo("FrameTime: " + std::to_string(frameTime) + "ms");
				},
				(ONE_SECOND + 0.0) / numFrames
			);
			numFrames = 0;
			lastTime = utils::GetGameTime();
		}
	}

	void Game::SetLevel(const std::string& newLevelPath) {
		if (CurrentLevel != nullptr) {
			//Level unloading logic
		}

		CurrentLevel = LevelCache->GetResource(newLevelPath);
		CurrentLevel->Initialize();
		CurrentLevel->BeginPlay();
	}

}
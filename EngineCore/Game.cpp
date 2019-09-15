//STD Headers
#include <iostream>
#include <utility>

//Library Headers


//Coati Headers
#include "AudioManager.h"
#include "Console.h"
#include "Configuration.h"
#include "Game.h"
#include "InputManager.h"
#include "MessageBus.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ThreadPool.h"
#include "WindowManager.h"

namespace EngineCore {

	Game::Game(const std::string& name) : GameName(std::move(name)) {
		FrameRate = 0;

		//Init Higher Level Game Objects
		InitGame();

		//Start game loop
		ExecuteGameLoop();
	}

	Game::~Game() {

	}

	void Game::InitGame() {
		//Initialize Engine Utilities
		GameThreadPool = std::make_shared<EngineUtils::ThreadPool>();
		GameResourceManager = std::make_shared<EngineUtils::ResourceManager>(GameThreadPool);

		//Initialize game window and input interface
		Window = std::make_shared<WindowManager>(GameName, 800, 600);
		
		//Initialize Renderer
		GameRenderer = std::make_unique<Renderer>(
			Window, 
			GameThreadPool,
			GameResourceManager,
			GameResourceManager->LoadResource<EngineUtils::Configuration>("Settings/RenderingConfig.lua")
		);
		
		//Initialize Input Manager
		GameInputManager = std::make_unique<InputManager>(
			Window->GetInputInterface(),
			GameThreadPool,
			GameResourceManager,
			GameResourceManager->LoadResource<EngineUtils::Configuration>("Settings/InputConfig.lua")
		);

		//Initialize Audio Manager
		GameAudioManager = std::make_unique<AudioManager>(
			GameThreadPool,
			GameResourceManager,
			GameResourceManager->LoadResource<EngineUtils::Configuration>("Settings/AudioConfig.lua")
			
		);
	}

	void Game::Update(double deltaTime) {
		//Send the deltaSeconds to the framerate updating function
		UpdateFramerate(deltaTime);

		CurrentLevel->Update(deltaTime);
	}

	void Game::Render() {
		GameRenderer->Render();
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		while (!Window->WindowTerminated()) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<double> deltaSeconds = currentTime - previousTime;

			GameInputManager->HandleInput();
			Update(deltaSeconds.count());
			Render();

			//Update previous time
			previousTime = currentTime;
		}
	}

	void Game::UpdateFramerate(double timeSinceLastFrame) {
		const int FRAME_LIMIT = 10;
		static int FrameCount;
		static double CumulativeFrameTime;
		
		CumulativeFrameTime += timeSinceLastFrame;
		
		if (FrameCount < FRAME_LIMIT) {
			FrameCount++;
		}
		else {
			FrameRate = static_cast<int>(FRAME_LIMIT / CumulativeFrameTime);
			FrameCount = 0;
			CumulativeFrameTime = 0;
		}
	}

}
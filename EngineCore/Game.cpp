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

	void Game::ProcessInput() {
		GameInputManager->HandleInput();
	}

	void Game::Update(double deltaSeconds) {
		//Send the deltaSeconds to the framerate updating function
		UpdateFramerate(deltaSeconds);

	}

	void Game::Render() {
		GameRenderer->Render();
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		while (!Window->WindowTerminated()) {
			//Get current time
			auto currentTime = Timer::now();
			std::chrono::duration<double> deltaSeconds = currentTime - previousTime;

			ProcessInput();
			Update(deltaSeconds.count());
			Render();

			//Update previous time
			previousTime = currentTime;
		}
	}

	void Game::UpdateFramerate(double timeSinceLastFrame) {
		const int NumFrames = 10;
		FrameQueue.push(timeSinceLastFrame);
		
		//Sums the queue if its of size 10
		if (FrameQueue.size() >= NumFrames) {
			double frameQueueSum = 0;
			while(!FrameQueue.empty()){
				frameQueueSum = frameQueueSum + (FrameQueue.front());
				FrameQueue.pop();
			}
			//Once the sum is completed, convert from seconds/10frames to frames and ship to FrameRate
			FrameRate = static_cast<int>(NumFrames / (frameQueueSum));
		}
	}

}
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

		//Set the current level to the default level
		SetLevel("Resources/Levels/DemoLevel.json");

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

		GameMessageBus = std::make_shared<MessageBus>();
		GameConsole = std::make_shared<Console>(GameMessageBus);
	}

	void Game::Update(double deltaTime) {
		//Send the deltaSeconds to the framerate updating function
		UpdateFramerate(deltaTime);

		CurrentLevel->Update(deltaTime);
	}

	void Game::Render() {
		GameRenderer->Render(CurrentLevel->GetScene());
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
		const static int ONE_SECOND = 1000;
		static auto lastTime = EngineUtils::GetGameTime();
		static int numFrames = 0;

		auto currentTime = EngineUtils::GetGameTime();
		numFrames++;

		if (currentTime - lastTime >= ONE_SECOND) {
			GameThreadPool->SubmitJob(
				[] (double frameTime){
					std::cout << "FrameTime: " << frameTime << "ms\n";
				},
				(ONE_SECOND + 0.0) / numFrames
			);
			numFrames = 0;
			lastTime = EngineUtils::GetGameTime();
		}



	}

	void Game::SetLevel(const std::string& newLevelPath) {
		if (CurrentLevel != nullptr) {
			//Level unloading logic
		}

		//CurrentLevel = GameResourceManager->GetResource<Level>(newLevelPath);
		CurrentLevel = GameResourceManager->GetResource<Level>(newLevelPath);
		CurrentLevel->SpawnEntities();
		CurrentLevel->BeginPlay();
	}

}
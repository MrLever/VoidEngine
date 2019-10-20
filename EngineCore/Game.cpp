//STD Headers
#include <utility>
#include <string>

//Library Headers


//Coati Headers
#include "AudioManager.h"
#include "Console.h"
#include "Configuration.h"
#include "Game.h"
#include "InputManager.h"
#include "MessageBus.h"
#include "Renderer.h"
#include "ResourceAllocator.h"
#include "ThreadPool.h"
#include "WindowManager.h"
#include "Logger.h"

namespace core {

	Game::Game(const std::string& configFile) : EngineConfig(configFile) {
		FrameRate = 0;
		
		//Load configuration data
		EngineConfig.Load();

		//Init Higher Level Game Objects
		InitGame();

		//Set the current level to the default level
		SetLevel(EngineConfig.GetAttribute<std::string>("DefaultLevel"));
		Window->ToggleCursor();

		//Start game loop
		ExecuteGameLoop();
	}

	Game::~Game() {

	}

	void Game::InitGame() {
		//Initialize Engine Utilities
		GameThreadPool = std::make_shared<utils::ThreadPool>();

		ConfigManager = std::make_shared<utils::ResourceAllocator<utils::Configuration>>(GameThreadPool);
		LevelCache = std::make_shared<utils::ResourceAllocator<Level>>(GameThreadPool);

		//Initialize game window and input interface
		Window = std::make_shared<WindowManager>(EngineConfig.GetAttribute<std::string>("GameName"), 800, 600);

		//Initialize Input Manager
		GameInputManager = std::make_shared<InputManager>(
			ConfigManager->LoadResource("Settings/InputConfig.json")
		);

		//Attach input manager to window to address hardware callbacks
		Window->SetInputManager(GameInputManager);

		//Initialize Renderer
		GameRenderer = std::make_unique<Renderer>(
			Window, 
			GameThreadPool,
			ConfigManager->LoadResource("Settings/RenderingConfig.json")
		);
		
		//Initialize Audio Manager
		GameAudioManager = std::make_unique<AudioManager>(
			GameThreadPool,
			ConfigManager->LoadResource("Settings/AudioConfig.json")
		);

		GameMessageBus = std::make_shared<MessageBus>();
		GameConsole = std::make_shared<Console>(GameMessageBus);
	}

	void Game::Update(float deltaTime) {
		if (deltaTime - 0.5f < std::numeric_limits<float>::epsilon()) {
			deltaTime = 0.5f;
		}

		UpdateFramerate(deltaTime);
		CurrentLevel->Update(deltaTime);
	}

	void Game::ProcessInput(float deltaTime) {
		Window->PollEvents();
		GameInputManager->ProcessInput(CurrentLevel->GetScene(), deltaTime);
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		while (!Window->WindowTerminated()) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<float> deltaSeconds = currentTime - previousTime;
			auto deltaTime = deltaSeconds.count();
			
			//Handle input
			ProcessInput(deltaTime);
			
			//Update the scene
			Update(deltaTime);
			
			//Draw the scene
			GameRenderer->Render(CurrentLevel.get());

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
			GameThreadPool->SubmitJob(
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
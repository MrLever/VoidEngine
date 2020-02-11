//STD Headers
#include <utility>
#include <string>

//Library Headers


//Void Engine Headers
#include "Game.h"

namespace core {

	Game::Game(const std::string& configFile) : EngineConfig(configFile) {
		FrameRate = 0;
		Terminated = false;
		Paused = false;
		
		EngineConfig.Load();

		Initialize();
		
		//Set the current level to the default level
		SetLevel(EngineConfig.GetAttribute<std::string>("defaultLevel"));

		//Start game loop
		ExecuteGameLoop();
	}

	Game::~Game() {
		utils::Logger::LogInfo("Game terminated!");
	}

	void Game::Initialize() {
		//Initialize Engine Utilities
		GameThreadPool = std::make_shared<utils::ThreadPool>();

		utils::ResourceAllocatorBase::EngineThreadPool = GameThreadPool;

		ConfigManager = std::make_shared<utils::ResourceAllocator<utils::Configuration>>();

		//Intialize EventBus
		GameEventBus = std::make_shared<EventBus>();

		//Initialize game window and input interface
		WindowData data{
			EngineConfig.GetAttribute<std::string>("gameName"),
			800,
			600
		};

		GameWindow = std::make_shared<Window>(GameEventBus.get(), data);

		//Initialize Input Manager
		GameInputManager = std::make_shared<InputManager>(
			GameEventBus.get(),
			ConfigManager->LoadResource("Settings/InputConfig.json")
			);

		//Initialize Renderer
		GameRenderer = std::make_unique<Renderer>(
			GameEventBus.get(),
			GameWindow,
			ConfigManager->LoadResource("Settings/RenderingConfig.json")
			);

		//Initialize Audio Manager
		GameAudioManager = std::make_unique<AudioManager>(
			GameThreadPool,
			ConfigManager->LoadResource("Settings/AudioConfig.json")
			);

		CorePhysicsEngine = std::make_unique<PhysicsEngine>(
			GameEventBus.get(),
			ConfigManager->LoadResource("Settings/PhysicsConfig.json")
			);
		BusNode = std::make_unique<GameEventBusNode>(GameEventBus.get(), this);
		
		//Create the level cache
		LevelCache = std::make_shared<utils::ResourceAllocator<Level>>();
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		
		while (!Terminated) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<float> deltaSeconds = currentTime - previousTime;
			auto deltaTime = deltaSeconds.count();

			//Handle input
			ProcessInput(deltaTime);

			//Dispatch any events that occurred since the last frame
			GameEventBus->DispatchEvents();

			//Update the scene
			if (!Paused) {
				Update(deltaTime);
			}

			//Draw the scene
			GameRenderer->Render(CurrentLevel.get());

			//Update previous time
			previousTime = currentTime;
		}

	}

	void Game::Update(float deltaTime) {
		if (deltaTime > 0.5f) {
			deltaTime = 0.5f;
		}

		UpdateFramerate(deltaTime);

		CorePhysicsEngine->Simulate(CurrentLevel.get(), deltaTime);
		CurrentLevel->Update(deltaTime);
	}

	void Game::ProcessInput(float deltaTime) {
		GameWindow->ProcessEvents();
		GameInputManager->ProcessInput(CurrentLevel.get(), deltaTime);
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

	void Game::HandleWindowClosed(WindowClosedEvent* event) {
		Terminated = true;
	}

	void Game::PauseGame(PauseGameEvent* event) {
		if (Paused) {
			GameInputManager->SetActiveInputMapping(CurrentLevel->GetControlFilePath());
		}
		else {
			GameInputManager->SetActiveInputMapping("Settings/Controls/MenuControls.json");
		}

		Paused = !Paused;
	}

	void Game::SetLevel(const std::string& newLevelPath) {
		if (CurrentLevel != nullptr) {
			//Level unloading logic
		}

		CurrentLevel = LevelCache->GetResource(newLevelPath);
		CurrentLevel->Initialize();
		GameInputManager->SetActiveInputMapping(CurrentLevel->GetControlFilePath());
		CurrentLevel->BeginPlay();
	}

}
//STD Headers
#include <utility>
#include <string>

//Library Headers


//Void Engine Headers
#include "Game.h"
#include "SceneLoader.h"
#include "platform/Platform.h"

namespace core {

	Game::Game(const std::string& configFile) : EngineConfig(configFile) {
		FrameRate = 0;
		Terminated = false;
		Paused = false;
		
		EngineConfig.Load();

		Initialize();
	
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

		//Initialize game window
		GameWindow = platform::MakeWindow(
			GameEventBus.get(), 
			WindowData {
				EngineConfig.GetAttribute<std::string>("gameName"),
				800,
				600
			}
		);

		//Initialize Input Manager
		GameInputManager = std::make_shared<InputManager>(
			GameEventBus.get(),
			ConfigManager->LoadResource("Settings/InputConfig.json")
		);

		//Initialize Renderer
		GameRenderer = std::make_shared<Renderer>(
			GameEventBus.get(),
			GameWindow->GetRenderingContext(),
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

		//Set the current level to the default level
		SetLevel(EngineConfig.GetAttribute<std::string>("defaultLevel"));
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		
		while (!Terminated) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<float> deltaSeconds = currentTime - previousTime;
			auto deltaTime = deltaSeconds.count();

			GameWindow->ProcessEvents();

			//Dispatch any events that occurred since the last frame
			GameEventBus->DispatchEvents();

			ActiveScene->ProcessInput(deltaTime);

			//Update the scene
			if (!Paused) {
				Update(deltaTime);
			}

			//Draw the scene
			ActiveScene->Draw();
			GameWindow->SwapBuffers();

			//Update previous time
			previousTime = currentTime;
		}

	}

	void Game::Update(float deltaTime) {
		if (deltaTime > 0.5f) {
			deltaTime = 0.5f;
		}

		UpdateFramerate(deltaTime);

		ActiveScene->Update(deltaTime);
	}

	void Game::UpdateFramerate(double timeSinceLastFrame) {
		const static int ONE_SECOND = 1000;
		static auto lastTime = utils::GetGameTime();
		static int numFrames = 0;

		auto currentTime = utils::GetGameTime();
		numFrames++;

		if (currentTime - lastTime >= ONE_SECOND) {

			utils::Logger::LogInfo(
				"FrameTime: " + 
				std::to_string((ONE_SECOND + 0.0) / numFrames) + 
				"ms"
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
			GameInputManager->SetActiveInputMapping(ActiveScene->GetControlFilePath());
		}
		else {
			GameInputManager->SetActiveInputMapping("Settings/Controls/MenuControls.json");
		}

		Paused = !Paused;
	}

	void Game::SetLevel(const std::string& newLevelPath) {
		if (ActiveScene != nullptr) {
			//Level unloading logic
		}

		ActiveScene = std::make_shared<Scene>(GameInputManager, GameRenderer, CorePhysicsEngine);
		GameSceneLoader.LoadLevel(ActiveScene.get(), newLevelPath);
		GameInputManager->SetActiveInputMapping(ActiveScene->GetControlFilePath());
		ActiveScene->BeginPlay();
	}

}
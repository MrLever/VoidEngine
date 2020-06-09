//STD Headers
#include <utility>
#include <string>

//Library Headers


//Void Engine Headers
#include "Game.h"
#include "Scene.h"
#include "platform/Platform.h"

namespace core {

	Game::Game(const std::string& configFile) : engineConfig(configFile) {
		isTerminated = false;
		isPaused = false;

		utils::Logger::LogInfo(std::string("Game launched with Working Directory: ") + std::filesystem::current_path().string());

		engineConfig.Load();

		Initialize();
	
		//Start game loop
		ExecuteGameLoop();
	}

	Game::~Game() {
		//Ensure that scene and all game objects are destroyed before destroying engine systems
		scene.reset(nullptr);
		eventListener.reset(nullptr);
		utils::Logger::LogInfo("Game terminated!");
	}

	void Game::Initialize() {
		//Initialize Engine Utilities
		threadPool = std::make_shared<utils::ThreadPool>();

		utils::ResourceAllocatorBase::EngineThreadPool = threadPool;

		//Intialize EventSystem
		eventSystem = std::make_unique<EventSystem>();
		eventListener.reset(new EventListener(eventSystem.get()));

		eventListener->SubscribeToEvent<WindowClosedEvent>(
			[this](WindowClosedEvent* windowEvent) {
				HandleWindowClosed(windowEvent);
			}
		);

		eventListener->SubscribeToEvent<InputActionEvent>(
			[this](InputActionEvent* event) {
				auto action = event->action;
				if (action.Action == "PauseGame" && action.Type == ActionType::PRESSED) {
					eventListener->PostEvent<PauseGameEvent>();
				}
			}
		);

		eventListener->SubscribeToEvent<PauseGameEvent>(
			[this](PauseGameEvent* pauseEvent) {
				PauseGame(pauseEvent);
			}
		);


		//Initialize game window
		window = platform::MakeWindow(
			eventSystem.get(), 
			WindowData {
				"SuperVoid",
				1280,
				720
			}
		);

		Renderer::Initialize(window->GetViewport());

		//Initialize Input Manager
		inputManager = std::make_shared<InputManager>(
			eventSystem.get(),
			configCache.LoadResource("Settings/InputConfig.json")
		);

		//Initialize Audio Manager
		audioManager = std::make_unique<AudioManager>(
			threadPool,
			configCache.LoadResource("Settings/AudioConfig.json")
		);

		physicsEngine = std::make_unique<PhysicsEngine>(
			eventSystem.get(),
			configCache.LoadResource("Settings/PhysicsConfig.json")
		);

		//Set the current level to the default level
		SetLevel(engineConfig.GetAttribute<std::string>("defaultLevel"));
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		
		while (!isTerminated) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<float> deltaSeconds = currentTime - previousTime;
			auto deltaTime = deltaSeconds.count();

			window->ProcessEvents();

			//Dispatch any events that occurred since the last frame
			eventSystem->DispatchEvents();

			scene->ProcessInput(deltaTime);

			//Update the scene
			if (!isPaused) {
				Update(deltaTime);
			}

			//Draw the scene
			scene->Draw();
			window->SwapBuffers();

			//Update previous time
			previousTime = currentTime;
		}

	}

	void Game::Update(float deltaTime) {
		if (deltaTime > 0.5f) {
			deltaTime = 0.5f;
		}

		UpdateFramerate(deltaTime);

		scene->Update(deltaTime);
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
		isTerminated = true;
	}

	void Game::PauseGame(PauseGameEvent* event) {
		if (isPaused) {
			inputManager->SetActiveInputMapping(scene->GetControlFilePath());
		}
		else {
			inputManager->SetActiveInputMapping("Settings/Controls/MenuControls.json");
		}

		isPaused = !isPaused;
	}

	void Game::SetLevel(const std::string& newLevelPath) {
		if (scene != nullptr) {
			//Level unloading logic
		}

		scene = std::make_unique<Scene>(newLevelPath, eventSystem.get(), inputManager, physicsEngine);
		inputManager->SetActiveInputMapping(scene->GetControlFilePath());
		scene->BeginPlay();
	}

}
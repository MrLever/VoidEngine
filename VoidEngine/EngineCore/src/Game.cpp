//STD Headers
#include <utility>
#include <string>

//Library Headers


//Void Engine Headers
#include "Game.h"
#include "Scene.h"
#include "platform/Platform.h"

namespace core {

	Game::Game(const std::string& configFile) : m_EngineConfig(configFile) {
		m_IsTerminated = false;
		m_IsPaused = false;

		utils::Logger::LogInfo(std::string("Game launched with Working Directory: ") + std::filesystem::current_path().string());

		m_EngineConfig.Load();

		Initialize();
	
		//Start game loop
		ExecuteGameLoop();
	}

	Game::~Game() {
		//Ensure that scene and all game objects are destroyed before destroying engine systems
		m_Scene.reset(nullptr);
		m_EventListener.reset(nullptr);
		utils::Logger::LogInfo("Game terminated!");
	}

	void Game::Initialize() {
		//Initialize Engine Utilities
		m_ThreadPool = std::make_shared<utils::ThreadPool>();

		//Provide thread pool access to resource allocation systems
		utils::ResourceAllocatorBase::EngineThreadPool = m_ThreadPool;

		//Intialize EventSystem
		m_EventSystem = std::make_unique<EventSystem>();
		m_EventListener.reset(new EventListener(m_EventSystem.get()));

		m_EventListener->SubscribeToEvent<WindowClosedEvent>(
			[this](WindowClosedEvent* windowEvent) {
				HandleWindowClosed(windowEvent);
			}
		);

		m_EventListener->SubscribeToEvent<InputActionEvent>(
			[this](InputActionEvent* event) {
				auto action = event->action;
				if (action.Action == "PauseGame" && action.Type == ActionType::PRESSED) {
					m_EventListener->PostEvent<PauseGameEvent>();
				}
			}
		);

		m_EventListener->SubscribeToEvent<PauseGameEvent>(
			[this](PauseGameEvent* pauseEvent) {
				PauseGame(pauseEvent);
			}
		);


		//Initialize game window
		m_Window = platform::MakeWindow(
			m_EventSystem.get(), 
			WindowData {
				"SuperVoid",
				1280,
				720
			}
		);

		Renderer::Initialize(m_Window->GetViewport());

		//Initialize Input Manager
		m_InputManager = std::make_shared<InputManager>(
			m_EventSystem.get(),
			m_ConfigCache.LoadResource("Config/InputConfig.json")
		);

		//Initialize Audio Manager
		m_AudioManager = std::make_unique<AudioManager>(
			m_ThreadPool,
			m_ConfigCache.LoadResource("Config/AudioConfig.json")
		);

		m_PhysicsEngine = std::make_unique<PhysicsEngine>(
			m_EventSystem.get(),
			m_ConfigCache.LoadResource("Config/PhysicsConfig.json")
		);

		//Set the current level to the default level
		SetLevel(m_EngineConfig.GetAttribute<std::string>("defaultLevel"));
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		
		while (!m_IsTerminated) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<float> deltaSeconds = currentTime - previousTime;
			auto deltaTime = deltaSeconds.count();

			m_Window->ProcessEvents();

			//Dispatch any events that occurred since the last frame
			m_EventSystem->DispatchEvents();

			m_Scene->ProcessInput(deltaTime);

			//Update the scene
			if (!m_IsPaused) {
				Update(deltaTime);
			}

			//Draw the scene
			m_Scene->Draw();
			m_Window->SwapBuffers();

			//Update previous time
			previousTime = currentTime;
		}

	}

	void Game::Update(float deltaTime) {
		if (deltaTime > 0.5f) {
			deltaTime = 0.5f;
		}

		UpdateFramerate(deltaTime);

		m_Scene->Update(deltaTime);
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
		m_IsTerminated = true;
	}

	void Game::PauseGame(PauseGameEvent* event) {
		if (m_IsPaused) {
			m_InputManager->SetActiveInputMapping(m_Scene->GetControlFilePath());
		}
		else {
			m_InputManager->SetActiveInputMapping("Config/Controls/MenuControls.json");
		}

		m_IsPaused = !m_IsPaused;
	}

	void Game::SetLevel(const std::string& newLevelPath) {
		if (m_Scene != nullptr) {
			//Level unloading logic
		}

		m_Scene = std::make_unique<Scene>(newLevelPath, m_EventSystem.get(), m_InputManager, m_PhysicsEngine);
		m_InputManager->SetActiveInputMapping(m_Scene->GetControlFilePath());
		m_Scene->BeginPlay();
	}

}
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
		m_FrameRate = 0;
		m_Terminated = false;
		m_Paused = false;

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
		m_ThreadPool = std::make_shared<utils::ThreadPool>();

		utils::ResourceAllocatorBase::EngineThreadPool = m_ThreadPool;

		//Intialize EventBus
		m_EventBus = std::make_shared<EventBus>();

		//Initialize game window
		m_Window = platform::MakeWindow(
			m_EventBus.get(), 
			WindowData {
				"SuperVoid",
				800,
				600
			}
		);

		Renderer::Initialize();

		//Initialize Input Manager
		m_InputManager = std::make_shared<InputManager>(
			m_EventBus.get(),
			m_ConfigCache.LoadResource("Settings/InputConfig.json")
		);

		//Initialize Audio Manager
		m_AudioManager = std::make_unique<AudioManager>(
			m_ThreadPool,
			m_ConfigCache.LoadResource("Settings/AudioConfig.json")
		);

		m_PhysicsEngine = std::make_unique<PhysicsEngine>(
			m_EventBus.get(),
			m_ConfigCache.LoadResource("Settings/PhysicsConfig.json")
		);

		m_CentralBusNode = std::make_unique<GameEventBusNode>(m_EventBus.get(), this);

		//Set the current level to the default level
		SetLevel(EngineConfig.GetAttribute<std::string>("defaultLevel"));
	}

	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		auto currentTime = Timer::now();
		
		while (!m_Terminated) {
			//Get current time
			currentTime = Timer::now();
			std::chrono::duration<float> deltaSeconds = currentTime - previousTime;
			auto deltaTime = deltaSeconds.count();

			m_Window->ProcessEvents();

			//Dispatch any events that occurred since the last frame
			m_EventBus->DispatchEvents();

			m_ActiveScene->ProcessInput(deltaTime);

			//Update the scene
			if (!m_Paused) {
				Update(deltaTime);
			}

			//Draw the scene
			m_ActiveScene->Draw();
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

		m_ActiveScene->Update(deltaTime);
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
		m_Terminated = true;
	}

	void Game::PauseGame(PauseGameEvent* event) {
		if (m_Paused) {
			m_InputManager->SetActiveInputMapping(m_ActiveScene->GetControlFilePath());
		}
		else {
			m_InputManager->SetActiveInputMapping("Settings/Controls/MenuControls.json");
		}

		m_Paused = !m_Paused;
	}

	void Game::SetLevel(const std::string& newLevelPath) {
		if (m_ActiveScene != nullptr) {
			//Level unloading logic
		}

		m_ActiveScene = std::make_shared<Scene>(m_EventBus.get(), m_InputManager, m_PhysicsEngine);
		m_SceneLoader.LoadLevel(m_ActiveScene.get(), newLevelPath);
		m_InputManager->SetActiveInputMapping(m_ActiveScene->GetControlFilePath());
		m_ActiveScene->BeginPlay();
	}

}
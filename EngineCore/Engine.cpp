//STD Headers

//Library Headers

//Void Engine Headers
#include "Engine.h"

namespace core {

	Engine::Engine(const std::string& engineConfig) : EngineConfig(std::move(engineConfig)) {
		
		EngineConfig.Load();

		//Initialize Engine Utilities
		GameThreadPool = std::make_shared<utils::ThreadPool>();

		ConfigManager = std::make_shared<utils::ResourceAllocator<utils::Configuration>>(GameThreadPool);

		//Intialize EventBus
		GameEventBus = std::make_shared<EventBus>();

		//Initialize game window and input interface
		WindowData data{
			EngineConfig.GetAttribute<std::string>("GameName"),
			800,
			600
		};

		GameWindow = std::make_shared<Window>(GameEventBus.get(), data);

		//Initialize Input Manager
		GameInputManager = std::make_shared<InputManager>(
			ConfigManager->LoadResource("Settings/InputConfig.json")
		);

		//Attach input manager to window to address hardware callbacks
		GameWindow->SetInputManager(GameInputManager);

		//Initialize Renderer
		GameRenderer = std::make_unique<Renderer>(
			GameWindow,
			GameThreadPool,
			ConfigManager->LoadResource("Settings/RenderingConfig.json")
			);

		//Initialize Audio Manager
		GameAudioManager = std::make_unique<AudioManager>(
			GameThreadPool,
			ConfigManager->LoadResource("Settings/AudioConfig.json")
			);

		GameMessageBus = std::make_shared<MessageBus>();
		GameConsole = std::make_shared<Console>(GameMessageBus.get());
	}

	void Engine::DispatchEvents() {
		GameEventBus->DispatchEvents();
	}

	ThreadPoolPtr Engine::GetThreadPool() {
		return GameThreadPool;
	}

	EventBusPtr Engine::GetEventBus() {
		return GameEventBus;
	}

	WindowManagerPtr Engine::GetWindowManager() {
		return GameWindow;
	}

	InputManagerPtr Engine::GetInputManager() {
		return GameInputManager;
	}

	std::string Engine::GetDefaultLevel() {
		return EngineConfig.GetAttribute<std::string>("DefaultLevel");
	}

	void Engine::PollInput() {
		GameWindow->PollEvents();
	}

	void Engine::ProcessInput(Level* level, const float deltaTime) {
		GameInputManager->ProcessInput(level, deltaTime);
	}

	void Engine::Render(Level* level) {
		GameRenderer->Render(level);
	}

}
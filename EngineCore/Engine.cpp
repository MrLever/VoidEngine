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
		GameConsole = std::make_shared<Console>(GameMessageBus.get());
	}

	ThreadPoolPtr Engine::GetThreadPool() {
		return GameThreadPool;
	}

	WindowManagerPtr Engine::GetWindowManager() {
		return Window;
	}

	InputManagerPtr Engine::GetInputManager() {
		return GameInputManager;
	}

	std::string Engine::GetDefaultLevel() {
		return EngineConfig.GetAttribute<std::string>("DefaultLevel");
	}

	void Engine::PollInput() {
		Window->PollEvents();
	}

	void Engine::ProcessInput(Level* level, const float deltaTime) {
		GameInputManager->ProcessInput(level, deltaTime);
	}

	bool Engine::GetIsRunning() {
		return !Window->WindowTerminated();
	}

	void Engine::Render(Level* level) {
		GameRenderer->Render(level);
	}

}
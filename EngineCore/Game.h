#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>


//Library Headers


namespace EngineCore {

	//Forward Class declarations
	class MessageBus;
	class WindowManager;

	class World;
	class Renderer;
	class InputManager;
	class AudioManager;
	class Console;


	class Game {
		using Timer = std::chrono::high_resolution_clock;
	private:
		//Private Class Members
		std::shared_ptr<MessageBus> GameMessageBus;
		std::shared_ptr<WindowManager> Window;

		std::unique_ptr<Console> GameConsole;
		std::unique_ptr<World> GameWorld;
		std::unique_ptr<Renderer> GameRenderer;
		std::unique_ptr<InputManager> GameInputManager;
		std::unique_ptr<AudioManager> GameAudioManager;

		std::string GameName;

		std::queue<double> FrameQueue;

		int FrameRate;

	public:
		//CTORS
		Game(std::string name);
		~Game();

	private:
		//Private member functions
		void InitGame();

		void ProcessInput();
		void Update(double deltaSeconds);
		void Render();

		void ExecuteGameLoop();

		void UpdateFramerate(double timeSinceLastFrame);
	};

}
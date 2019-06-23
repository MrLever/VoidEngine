//STD Headers
#include <iostream>
#include <utility>

//Library Headers


//Coati Headers
#include "Game.h"
#include "Console.h"
#include "MessageBus.h"
#include "WindowManager.h"
#include "World.h"
#include "Renderer.h"
#include "InputManager.h"
#include "AudioManager.h"

namespace EngineCore {

	//CTORS
	Game::Game(std::string name) : GameName(std::move(name)) {
		FrameRate = 0;

		//Init Higher Level Game Objects
		InitGame();

		//Start game loop
		ExecuteGameLoop();

	}

	Game::~Game() {
		std::cout << "Goodbye!";
	}

	//Private Functions

	//Initialize higher level game objects
	void Game::InitGame() {

		GameMessageBus = std::make_shared<MessageBus>();
		Window = std::make_shared<WindowManager>(GameName, 800, 600);

		GameConsole = std::make_unique<Console>(GameMessageBus);
		GameWorld = std::make_unique<World>(GameMessageBus);
		GameRenderer = std::make_unique<Renderer>(Window);
		GameInputManager = std::make_unique<InputManager>(
			GameMessageBus, 
			Window->GetInputInterface()
		);
		GameAudioManager = std::make_unique<AudioManager>(GameMessageBus);
	}

	void Game::ProcessInput() {
		GameInputManager->HandleInput();
	}

	void Game::Update(double deltaSeconds) {
		//Send the deltaSeconds to the framerate updating function
		UpdateFramerate(deltaSeconds);

		//Triggers Events
		GameMessageBus->DispatchMessages();

		//Ticks actors
		GameWorld->Update(deltaSeconds);
	}

	void Game::Render() {
		GameRenderer->Render();
	}


	void Game::ExecuteGameLoop() {
		auto previousTime = Timer::now();
		while (!Window->WindowTerminated()) {
			//Get current time
			auto currentTime = Timer::now();
			std::chrono::duration<double> deltaSeconds = currentTime - previousTime;

			ProcessInput();
			Update(deltaSeconds.count());
			Render();

			//Update previous time
			previousTime = currentTime;
		}
	}

	void Game::UpdateFramerate(double timeSinceLastFrame) {
		const int NumFrames = 10;
		FrameQueue.push(timeSinceLastFrame);
		
		//Sums the queue if its of size 10
		if (FrameQueue.size() >= NumFrames) {
			double frameQueueSum = 0;
			while(!FrameQueue.empty()){
				frameQueueSum = frameQueueSum + (FrameQueue.front());
				FrameQueue.pop();
			}
			//Once the sum is completed, convert from seconds/10frames to frames and ship to FrameRate
			FrameRate = static_cast<int>(NumFrames / (frameQueueSum));
		}
	}

}
#pragma once
//STD Headers
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <deque>

//Library Headers

//Void Engine Headers
#include "Configurable.h"
#include "Entity.h"
#include "ThreadPool.h"
#include "ResourceManager.h"
#include "MessageBusNode.h"
#include "KeyboardInput.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"

namespace EngineCore {

	//Forward Class declarations
	class MessageBus;

	/**
	 * @class InputManager
	 * @brief The InputManager is responsible for processing input events to handle debouncing
	 *        and detect higher order patterns like double-taps and chords 
	 */
	class InputManager : public EngineUtils::Configurable {
	public:
		/**
		 * Constructor
		 * @param playerInterface the Engine's interface to all HID devices connected to the game
		 */
		InputManager(
			ThreadPoolPtr threadPool,
			ResourceManagerPtr resourceManager,
			const EngineUtils::ResourceHandle& configuration
		);

		/**
		 * Destructor
		 */
		~InputManager() = default;

		/**
		 * Proccesses keyboard input events
		 * @param input The keyboard input to process
		 */
		void ReportInput(const KeyboardInput& input);

		/**
		 * Proccesses mouse input events
		 * @param input The mouse input to process
		 */
		void ReportInput(const MouseInput& input);

		/**
		 * Proccesses gamepad input events
		 * @param input The gamepad input to process
		 */
		void ReportInput(const GamepadInput& input);

		/**
		 * Instructs the input manager to process and dispatch events to the game entities
		 */
		void ProcessInput(const std::vector<Entity*> scene, float deltaTime);

	private:
		/**
		 * Applies input configuration settings 
		 */
		void Configure() override;

		/**
		 * Helper function to dispatch events to a scene
		 * @param scene The scene to dispatch events to
		 * @param event The event to dispatch
		 */
		void DispatchEvent(
			const std::vector<EngineCore::Entity*>& scene, 
			const EngineCore::InputEvent& event, 
			float deltaTime
		);

		/** Buffer for unprocessed keyboard inputs */
		std::deque<KeyboardInput> KeyboardInputBuffer;

		/** Buffer for unprocessed mouse inputs */
		std::deque<MouseInput> MouseInputBuffer;

		/** Buffer for unprocessed Gamepad inputs */
		std::deque<GamepadInput> GamepadInputBuffer;

		/** The game's active thread pool */
		ThreadPoolPtr GameThreadPool;

		/** The game's active resource manager */
		ResourceManagerPtr GameResourceManager;

	};

}
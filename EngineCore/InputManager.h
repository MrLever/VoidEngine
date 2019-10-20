#pragma once
//STD Headers
#include <memory>
#include <unordered_map>
#include <deque>

//Library Headers

//Void Engine Headers
#include "Configurable.h"
#include "Configuration.h"
#include "Entity.h"
#include "ThreadPool.h"
#include "ResourceAllocator.h"
#include "MessageBusNode.h"
#include "KeyboardInput.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"
#include "InputAxis.h"

namespace core {

	//Forward Class declarations
	class MessageBus;
	class Level;

	/**
	 * @class InputManager
	 * @brief The InputManager is responsible for processing input events to handle debouncing
	 *        and detect higher order patterns like double-taps and chords 
	 */
	class InputManager : public utils::Configurable {
	public:
		/**
		 * Constructor
		 * @param playerInterface the Engine's interface to all HID devices connected to the game
		 */
		InputManager(const utils::ResourceHandle<utils::Configuration>& configuration);

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
		 * Proccesses gamepad input events
		 * @param input The gamepad input to process
		 */
		void ReportInput(const InputAxisReport& input);

		/**
		 * Instructs the input manager to process and dispatch events to the game entities
		 * @param scene The scene of entities to propogate commands to
		 * @param deltaTime the time step for input operations
		 */
		void ProcessInput(Level* scene, float deltaTime);

	private:
		/**
		 * Applies input configuration settings 
		 */
		void Configure() override;

		/**
		 * Dispatches InputEvents to Entity-Component System
		 * @param scene The scene to dispatch events to
		 * @param event The event to dispatch
		 */
		void DispatchEvent(
			const std::vector<core::Entity*>& scene, 
			const InputEvent& event, 
			float deltaTime
		);

	    /**
		 * Dispatchs InputAxisReports to Entity-Component System
		 * @param scene The scene to dispatch events to
		 * @param event The event to dispatch
		 */
		void DispatchEvent(
			const std::vector<core::Entity*>& scene, 
			const InputAxisReport& axisData, 
			float deltaTime
		);

		/** Buffer for unprocessed keyboard inputs */
		std::deque<KeyboardInput> KeyboardInputBuffer;

		/** Buffer for unprocessed mouse inputs */
		std::deque<MouseInput> MouseInputBuffer;

		/** Buffer for unprocessed Gamepad inputs */
		std::deque<GamepadInput> GamepadInputBuffer;

		/** Buffer for unprocessed Input Axis data */
		std::deque<InputAxisReport> InputAxisDataBuffer;

		/** Maps certain keyboard inputs to InputAxes */
		std::unordered_map<KeyboardButton, std::shared_ptr<InputAxis>> KeyboardAxisBindings;
	};

}

using InputManagerPtr = std::shared_ptr<core::InputManager>;
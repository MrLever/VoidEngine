#pragma once
//STD Headers
#include <memory>
#include <unordered_map>
#include <unordered_set>

//Library Headers

//Coati Headers
#include "Configurable.h"
#include "EngineInterface.h"
#include "MessageBusNode.h"
#include "KeyboardInput.h"
#include "Keybindings.h"
#include "InputInterfaceManager.h"


namespace EngineCore {

	//Forward Class declarations
	class MessageBus;
	class InputEvent;

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
			std::shared_ptr<InputInterfaceManager> playerInterface, 
			EngineInterfacePtr voidEngineInterface, 
			const EngineUtils::ResourceHandle& configuration
		);

		/**
		 * Destructor
		 */
		~InputManager() = default;

		/**
		 * Polls and process all input events for the current frame
		 */
		void HandleInput();

	private:
		/**
		 * Polls and processes keyboard events from the current frame
		 */
		void HandleKeyboard();

		/**
		 * Polls and processes mouse events from the current frame
		 */
		void HandleMouse();

		/**
		 * Polls and processes gamepad events fromt he current frame
		 */
		void HandleGamepad();

		/**
		 * Applies input configuration settings 
		 */
		void Configure() override;

		/** The keybindings currently used by the input manager */
		Keybindings Bindings;

		/** The engine's current input interface */
		std::shared_ptr<InputInterfaceManager> PlayerInterface;
		
		/** Interface the Input Manager uses to access Engine Utility classes */
		std::shared_ptr<EngineInterface> VoidEngineInterface;

	};

}
#pragma once
//STD Headers
#include <memory>
#include <unordered_map>
#include <deque>

//Library Headers

//Void Engine Headers
#include "AxisInput.h"
#include "AxisInputAction.h"
#include "Configurable.h"
#include "ControlLayout.h"
#include "EventBusNode.h"
#include "Entity.h"
#include "ThreadPool.h"
#include "ResourceAllocator.h"
#include "MessageBusNode.h"
#include "KeyboardInput.h"
#include "KeyboardInputEvent.h"
#include "MouseInput.h"
#include "MouseMovedEvent.h"
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
	class InputManager : public EventBusNode, public utils::Configurable {
	public:
		/**
		 * Constructor
		 * @param playerInterface the Engine's interface to all HID devices connected to the game
		 */
		InputManager(
			EventBus* bus, 
			const utils::ResourceHandle<utils::Configuration>& configuration,
			std::shared_ptr<utils::ThreadPool> threadPool
		);

		/**
		 * Destructor
		 */
		~InputManager() = default;

		/**
		 * Allows node to receive and process events from EventBus
		 * @param event The event to process
		 */
		void ReceiveEvent(Event* event) override;

		/**
		 * Allows EventBus to query the node's subscription, and filter events accordingly
		 */
		virtual unsigned GetSubscription() /** override */;

		/**
		 * Function to report incomming raw input. 
		 * @param input The input to capture
		 * @tparam T The type of input being supplied
		 * @note T can be deduced by the compiler.
		 */
		template <class T>
		void ReportInput(const T& input);

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

		/** Deadzone used to filter joystick input */
		float JoystickDeadzone;

		/** Resource Cache for Input configurations */
		utils::ResourceAllocator<ControlLayout> ControlLayoutCache;

		std::shared_ptr<ControlLayout> DefaultControls;

		std::shared_ptr<ControlLayout> ActiveControls;

		std::deque<InputAction> InputActionBuffer;

		std::deque<AxisInputAction> AxisUpdateBuffer;
		
		/** Buffer for unprocessed Input Axis data */
		std::deque<AxisInput> AxisInputBuffer;

		/** Maps certain keyboard inputs to InputAxes */
		std::unordered_map<KeyboardButton, std::shared_ptr<InputAxis>> KeyboardAxisBindings;
	};

	template<class T>
	inline void InputManager::ReportInput(const T& input) {
		if (ActiveControls->IsBound(input)) {
			if (ActiveControls->IsBoundToAxis(input)) {
				auto mapping = ActiveControls->GetAxisMapping(input);
				ActiveControls->UpdateAxis(mapping);
				auto update = ActiveControls->PollAxis(mapping.AxisName);

				AxisUpdateBuffer.push_back(update);
			}
			else if(ActiveControls->IsBoundToAction(input)) {
				InputActionBuffer.push_back(ActiveControls->GetActionMapping(input));
			}
		}
		else if (DefaultControls->IsBound(input)) {
			if (ActiveControls->IsBoundToAxis(input)) {
				auto mapping = DefaultControls->GetAxisMapping(input);
				ActiveControls->UpdateAxis(mapping);
				auto update = DefaultControls->PollAxis(mapping.AxisName);

				AxisUpdateBuffer.push_back(update);
			}
			else if (ActiveControls->IsBoundToAction(input)) {
				InputActionBuffer.push_back(DefaultControls->GetActionMapping(input));
			}
		}
	}

	template <>
	inline void InputManager::ReportInput<AxisInput>(const AxisInput& input) {
		if (ActiveControls->IsBound(input)) {
			if (ActiveControls->IsBoundToAxis(input)) {
				AxisUpdateBuffer.push_back(ActiveControls->GetAxisMapping(input));
			}
		}
		else if (DefaultControls->IsBound(input)) {
			if (DefaultControls->IsBoundToAxis(input)) {
				AxisUpdateBuffer.push_back(DefaultControls->GetAxisMapping(input));
			}
		}
	}

}

using InputManagerPtr = std::shared_ptr<core::InputManager>;
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
#include "KeyboardButtonEvent.h"
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
			const utils::ResourceHandle<utils::Configuration>& configuration
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
		 * Applies input configuration settings 
		 */
		void Configure() override;

		/**
		 * Function to report incomming raw input. 
		 * @param input The input to capture
		 * @tparam T The type of input being supplied
		 * @note T can be deduced by the compiler.
		 */
		template <class T>
		void CaptureInput(const T& input);

		/**
		 * Instructs the input manager to process and dispatch events to the game entities
		 * @param scene The scene of entities to propogate commands to
		 * @param deltaTime the time step for input operations
		 */
		void ProcessInput(Level* scene, float deltaTime);

		void SetActiveInputMapping(const std::string& profilePath);

	private:
		/**
		 * Dispatches queued input actions to the scene
		 * @param scene The scene to dispatch input to
		 * @param deltaTime The current time step
		 */
		void ProcessInputActions(Level* scene, float deltaTime);

		/**
		 * Dispatches queued input actions to the scene
		 * @param scene The scene to dispatch input to
		 * @param deltaTime The current time step
		 */
		void ProcessAxisUpdates(Level* scene, float deltaTime);

		/** Deadzone used to filter joystick input */
		float JoystickDeadzone;

		/** Resource Cache for Input configurations */
		utils::ResourceAllocator<ControlLayout> ControlLayoutCache;

		/** Pointer to the engine-default control layout */
		std::shared_ptr<ControlLayout> DefaultControls;

		/** Pointer to the active level control layout */
		std::shared_ptr<ControlLayout> ActiveControls;

		/** Buffer of input actions to dispatch to entities on next update */
		std::deque<InputAction> InputActionBuffer;

		/** Buffer of axis updates to dispatch to entities on next update */
		std::deque<AxisInputAction> AxisUpdateBuffer;
	};

	template<class T>
	inline void InputManager::CaptureInput(const T& input) {
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
			if (DefaultControls->IsBoundToAxis(input)) {
				auto mapping = DefaultControls->GetAxisMapping(input);
				DefaultControls->UpdateAxis(mapping);
				auto update = DefaultControls->PollAxis(mapping.AxisName);

				AxisUpdateBuffer.push_back(update);
			}
			else if (DefaultControls->IsBoundToAction(input)) {
				InputActionBuffer.push_back(DefaultControls->GetActionMapping(input));
			}
		}
	}

	template <>
	inline void InputManager::CaptureInput<AxisInput>(const AxisInput& input) {
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
#pragma once
//STD Headers
#include <memory>
#include <unordered_map>
#include <deque>

//Library Headers

//Void Engine Headers
#include "utils/configuration/Configurable.h"
#include "utils/threading/ThreadPool.h"
#include "utils/resource/ResourceAllocator.h"

#include "core/event_system/EventBusNode.h"
#include "core/event_system/events/KeyboardButtonEvent.h"
#include "core/event_system/events/MouseMovedEvent.h"
#include "core/gameplay_framework/Entity.h"
#include "core/input/InputAxis.h"
#include "core/input/definitions/AxisInput.h"
#include "core/input/AxisInputAction.h"
#include "core/input/ControlLayout.h"
#include "core/input/definitions/GamepadInput.h"
#include "core/input/definitions/KeyboardInput.h"
#include "core/input/definitions/MouseInput.h"


namespace core {

	//Forward Class declarations
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
		void ProcessInput(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime);

		void SetActiveInputMapping(const std::string& profilePath);

	private:
		/**
		 * Dispatches queued input actions to the scene
		 * @param scene The scene to dispatch input to
		 * @param deltaTime The current time step
		 */
		void ProcessInputActions(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime);

		/**
		 * Dispatches queued input actions to the scene
		 * @param scene The scene to dispatch input to
		 * @param deltaTime The current time step
		 */
		void ProcessAxisUpdates(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime);

		/** Deadzone used to filter joystick input */
		float JoystickDeadzone;

		/** Resource Cache for Input configurations */
		utils::ResourceAllocator<ControlLayout> m_ControlLayoutCache;

		/** Pointer to the engine-default control layout */
		std::shared_ptr<ControlLayout> m_DefaultControls;

		/** Pointer to the active level control layout */
		std::shared_ptr<ControlLayout> m_ActiveControls;

		/** Buffer of input actions to dispatch to entities on next update */
		std::deque<InputAction> m_InputActionBuffer;

		/** Buffer of axis updates to dispatch to entities on next update */
		std::deque<AxisInputAction> m_AxisUpdateBuffer;
	};

	template<class T>
	inline void InputManager::CaptureInput(const T& input) {
		if (m_ActiveControls->IsBound(input)) {
			if (m_ActiveControls->IsBoundToAxis(input)) {
				auto mapping = m_ActiveControls->GetAxisMapping(input);
				m_ActiveControls->UpdateAxis(mapping);
				auto update = m_ActiveControls->PollAxis(mapping.AxisName);

				m_AxisUpdateBuffer.push_back(update);
			}
			else if(m_ActiveControls->IsBoundToAction(input)) {
				m_InputActionBuffer.push_back(m_ActiveControls->GetActionMapping(input));
			}
		}
		else if (m_DefaultControls->IsBound(input)) {
			if (m_DefaultControls->IsBoundToAxis(input)) {
				auto mapping = m_DefaultControls->GetAxisMapping(input);
				m_DefaultControls->UpdateAxis(mapping);
				auto update = m_DefaultControls->PollAxis(mapping.AxisName);

				m_AxisUpdateBuffer.push_back(update);
			}
			else if (m_DefaultControls->IsBoundToAction(input)) {
				m_InputActionBuffer.push_back(m_DefaultControls->GetActionMapping(input));
			}
		}
	}

	template <>
	inline void InputManager::CaptureInput<AxisInput>(const AxisInput& input) {
		if (m_ActiveControls->IsBound(input)) {
			if (m_ActiveControls->IsBoundToAxis(input)) {
				m_AxisUpdateBuffer.push_back(m_ActiveControls->GetAxisMapping(input));
			}
		}
		else if (m_DefaultControls->IsBound(input)) {
			if (m_DefaultControls->IsBoundToAxis(input)) {
				m_AxisUpdateBuffer.push_back(m_DefaultControls->GetAxisMapping(input));
			}
		}
	}

}

using InputManagerPtr = std::shared_ptr<core::InputManager>;
#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Entity.h"
#include "Input.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"
#include "Vector.h"
#include "Rotator.h"
#include "TypeUtils.h"

namespace core {
	
	/**
	 * @class Component
	 * @brief Base class for all components in the engine. Compnents allow
	 *        Entities to respond to engine commands or player actions
	 */
	class Component {
	public:
		/**
		 * Constructor
		 */
		Component();

		/**
		 * Set's the component's owner
		 */
		void SetParent(Entity* parent);

		/**
		 * Set's the component's initialization data
		 */
		void SetComponentData(const nlohmann::json& data);

		/**
		 * Applies component data to this object
		 */
		virtual void Initialize() = 0;

		/**
		 * Function to allow this component to process input
		 * @param input Input from the keyboard to process
		 */
		virtual void Input(const InputAction& input, float deltaTime);

		/**
		 * Function to allow this component to process input
		 * @param input Input axis data to process
		 */
		virtual void Input(const AxisInputAction& input, float deltaTime);

		/**
		 * Defines how a component processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(float deltaTime);

		/**
		 * Defines how a component is drawn
		 */
		virtual void Draw();

		/**
		 * Accessors for Position
		 */
		void SetPosition(const math::Vector3& position);
		math::Vector3 GetPosition() const;

		/**
		 * Set's this component's rotation
		 * @param position The position to use
		 */
		void SetRotation(const math::Rotator& rotation);

		/**
		 * Returns name of dynamic Component Type
		 */
		virtual utils::Name GetTypename() = 0;

		/**
		 * Returns name of static Component Type
		 */
		static utils::Name GetStaticTypename();

	protected:
		/** The component's position */
		math::Vector3 Position;
		
		/** The component's rotation */
		math::Quaternion Rotation;

		/** Data used to initialize component */
		nlohmann::json ComponentData;

		/** The component's parent */
		Entity* Parent;
	};
}
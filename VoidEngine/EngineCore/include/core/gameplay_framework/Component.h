#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"

#include "utils/TypeUtils.h"

#include "core/gameplay_framework/Entity.h"
#include "core/input/definitions/Input.h"
#include "core/input/definitions/KeyboardInput.h"
#include "core/input/definitions/MouseInput.h"
#include "core/input/definitions/GamepadInput.h"

namespace core {
	
	/**
	 * @class Component
	 * @brief Base class for all components in the engine. Compnents allow
	 *        Entities to respond to engine commands or player actions
	 */
	class Component : public utils::FactoryConstructible {
		friend class Entity;
		
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(Component)
	
public:
		/**
		 * Constructor
		 */
		Component();

		/**
		 * Destructor
		 */
		virtual ~Component();

		/**
		 * Accessors for the component's owner
		 */
		Entity* GetParent();

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
		 * @return Distance between the parent entity of these two components
		 */
		float GetDistance(Component* other) const;

		/**
		 * @return Distance squared between the parent entity of these two components
		 */
		float GetDistanceSquared(Component* other) const;

		/**
		 * @return The position of this component's parent
		 */
		math::Vector3 GetPosition() const;

		/**
		 * Defines how a component processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(float deltaTime);

		/**
		 * Defines how a component is drawn
		 */
		virtual void Draw();

	protected:
		/** The component's parent */
		Entity* parent;
	
		/** Read only pointer to the parent entity's transform */
		Transform* transform;
	};
}
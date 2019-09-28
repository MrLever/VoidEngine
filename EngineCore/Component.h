#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "Input.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"
#include "Vector.h"
#include "Rotator.h"

namespace EngineCore {
	class Component {
	public:
		/**
		 * Constructor
		 * @param parent This component's owner
		 */
		Component(Entity* parent);

		/**
		 * Function to allow this component to process input
		 * @param input Input fromt the keyboard to process
		 */
		virtual void Input(const InputEvent& input, float deltaTime);

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
		 * Set's this component's position
		 * @param position The position to use
		 */
		void SetPosition(const EngineMath::Vector3& position);

		/**
		 * Set's this component's rotation
		 * @param position The position to use
		 */
		void SetRotation(const EngineMath::Rotator& rotation);

	protected:
		/** The component's position */
		EngineMath::Vector3 Position;
		
		/** The component's rotation */
		EngineMath::Rotator Rotation;

		/** The component's parent */
		Entity* Parent;
	};
}
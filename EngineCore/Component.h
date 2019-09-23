#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Input.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"

namespace EngineCore {
	class Entity;

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
		virtual void Input(const KeyboardInput& input);

		/**
		 * Function to allow this component to process input
		 * @param input Input fromt the mouse to process
		 */
		virtual void Input(const MouseInput& input);

		/**
		 * Function to allow this component to process input
		 * @param input Input fromt the gamepad to process
		 */
		virtual void Input(const GamepadInput& input);

		/**
		 * Defines how a component processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(float deltaTime);

		/**
		 * Defines how a component is drawn
		 */
		virtual void Draw();


	private:
		Entity* Parent;
	};
}
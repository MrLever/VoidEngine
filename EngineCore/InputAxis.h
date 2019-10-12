#pragma once
//STD Headers
#include <string>
#include <unordered_map>

//Library Headers

//Void Engine Headers
#include "Name.h"
#include "InputAxisReport.h"
#include "KeyboardInput.h"

namespace core {

	/**
	 * @class InputAxis
	 * @brief InputAxis is a class used to digital inputs into analog inputs
	 * @note Analog Inputs can directly generate InputAxisReports, while discrete 
	 *       keys need this class.
	 */
	class InputAxis {
	public:
		/**
		 * Constructor
		 * @param name The input axis' name
		 */
		InputAxis(const std::string& name);

		/**
		 * Update the input axis based on new input
		 * @param input The input to use when updating 
		 */
		void UpdateAxis(const KeyboardInput& input);

		/**
		 * Query the state of the Axis
		 * @return A report of the axis' name and value
		 */
		InputAxisReport Poll() const;

		/**
		 * Add a keybinding to the behavior of this axis
		 * @param input The input to bind
		 * @param value The effect this input has on the axis
		 */
		void AddBinding(const KeyboardInput& input, float value);

		/**
		 * Remove a keybinding from the behavior of the axis
		 * @param input The key to unbind
		 */
		void RemoveBinding(const KeyboardInput& input);

	private:
		/** The name of the axis */
		utils::Name AxisName;

		/** The axis' current reading */
		float Value;

		/** The keybindings for this axis */
		std::unordered_map<KeyboardInput, float> Keybindings;
	};

}

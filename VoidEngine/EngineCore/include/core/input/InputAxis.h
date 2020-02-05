#pragma once
//STD Headers
#include <string>
#include <unordered_map>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

#include "core/input/definitions/KeyboardInput.h"

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
		 * Constructor
		 * @param name The input axis' name
		 */
		InputAxis(const utils::Name& name);

		/**
		 * Update the input axis based on new input
		 * @param input The input to use when updating 
		 */
		void UpdateAxis(float value);

		/**
		 * Query the state of the Axis
		 * @return A report of the axis' name and value
		 */
		float Poll() const;

		utils::Name GetAxisName() const;

		bool operator== (const InputAxis& other) const;

	private:
		/** The name of the axis */
		utils::Name AxisName;

		/** The axis' current reading */
		float Value;
	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<core::InputAxis> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const core::InputAxis& t) const {
			return static_cast<std::size_t>(t.GetAxisName().ID);
		}

	};
}

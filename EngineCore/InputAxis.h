#pragma once
//STD Headers
#include <unordered_map>
#include <list>
#include <string>

//Library Headers

//Coati Headesr
#include "KeyboardInput.h"
#include "Name.h"

namespace EngineCore {

	/**
	 * @class InputAxis
	 * @brief An input Axis represents a bounded one-dimensional axis that can be 
	 *        controlled by both digital and analogue input methods
	 */
	class InputAxis	{
	public:
		/**
		 * Constructor
		 * @param AxisName Name used to uniquely identify axes
		 */
		InputAxis(std::string AxisName);
		
		/**
		 * Destructor
		 */
		~InputAxis();

		/**
		 * Equality comparison operator overload
		 */
		bool operator==(const InputAxis& other);

		/**
		 * Adds a binding to the axis
		 * @param input The input the will trigger the axis
		 * @param scale The value that input will apply to the axis' state
		 */
		void AddBinding(KeyboardButton input, double scale);

		/**
		 * Getter for the Axis' unique identifier
		 * @return the Axis' name
		 */
		EngineUtils::Name GetName() const;

		/**
		 * Member function to allow owning object to manipulate the state
		 * of the input axis through input events
		 */
		void UpdateAxis(const KeyboardInput& input);

		/**
		 * Resets the axis to a neutral state
		 */
		void Reset();

		/**
		 * Allows outside objects to poll the state of the InputAxis
		 * @return the Axis' current value
		 */
		double Poll() const;

	private:
		/**
		 * Applies the input's scale to the axis
		 * @param input The input to apply
		 */
		void TriggerBinding(const KeyboardInput& input);

		/**
		 * Properly handles key-release actions for digital bindings
		 */
		void ReleaseBinding(const KeyboardInput& input);

		/** Map to define how inputs will affect this axis */
		std::unordered_map<KeyboardButton, double> AxisBindings;

		/** Que of digital commands to the axis */
		std::list<KeyboardButton> CommandQueue;

		/** The current value of this axis */
		double AxisValue;

		/** The Axis' unique identifier */
		EngineUtils::Name AxisName;
	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> 
	struct hash<EngineCore::InputAxis> { //Class to define hash function for Keyboard Input
		//Hash functor
		std::size_t operator()(const EngineCore::InputAxis& axis) const {
			return axis.GetName().ID;
		}

	};
}
#pragma once
//STD Headers
#include <functional>
#include <unordered_map>

//Library Headers

//Void Engine Headers

namespace core {
	enum class RawAxisType : unsigned {
		BUTTON_PRESSED,
		BUTTON_RELEASED,
		GAMEPAD_JOYSTICK_LEFT_X,
		GAMEPAD_JOYSTICK_LEFT_Y,
		GAMEPAD_JOYSTICK_RIGHT_X,
		GAMEPAD_JOYSTICK_RIGHT_Y,
		MOUSE_X,
		MOUSE_Y,
		ERROR_AXIS
	};

	static std::unordered_map<std::string, RawAxisType> StringToAxisMap = {
		{"BUTTON_PRESSED", RawAxisType::BUTTON_PRESSED},
		{"BUTTON_RELEASED", RawAxisType::BUTTON_RELEASED},
		{"GAMEPAD_JOYSTICK_LEFT_X", RawAxisType::GAMEPAD_JOYSTICK_LEFT_X},
		{"GAMEPAD_JOYSTICK_LEFT_Y", RawAxisType::GAMEPAD_JOYSTICK_LEFT_Y},
		{"GAMEPAD_JOYSTICK_RIGHT_X", RawAxisType::GAMEPAD_JOYSTICK_RIGHT_X},
		{"GAMEPAD_JOYSTICK_RIGHT_Y", RawAxisType::GAMEPAD_JOYSTICK_RIGHT_Y},
		{"MOUSE_X", RawAxisType::MOUSE_X},
		{"MOUSE_Y", RawAxisType::MOUSE_Y}
	};

	static RawAxisType DeserializeRawAxis(const std::string& axis) {
		if (StringToAxisMap.find(axis) == StringToAxisMap.end()) {
			return RawAxisType::ERROR_AXIS;
		}

		return StringToAxisMap[axis];
	}

	/**
	 * @class AxisInput
	 * @brief Wrapper class to capture raw axis input, and convert button inputs into Axis data
	 */
	class AxisInput {
	public:
		/**
		 * Constructor
		 */
		AxisInput(RawAxisType axis, float value);

		/**
		 * Getter for Axis
		 */
		RawAxisType GetAxisSource() const;

		/**
		 * Getter for Axis value
		 */
		float GetAxisValue() const;

		/**
		 * Equality comparison override
		 */
		bool operator== (const AxisInput& other) const;

	private:
		/** The source of this AxisInput */
		RawAxisType Axis;

		/** The Axis reading being reported */
		float AxisValue;
	};
}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<core::AxisInput> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const core::AxisInput& t) const {
			return static_cast<std::size_t>(t.GetAxisSource());
		}

	};
}
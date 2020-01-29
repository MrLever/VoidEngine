#pragma once
//STD Headers
#include <unordered_map>
#include <unordered_set>

//Library Headers

//Void Engine Headers
#include "utils/resource/JsonResource.h"
#include "AxisInputAction.h"
#include "InputAction.h"
#include "AxisInput.h"
#include "InputAxis.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"

namespace core {

	class ControlLayout : public utils::JsonResource {
	public:
		/**
		 * Constructor
		 */
		ControlLayout(const std::string& filePath);

		/**
		 * Allows the resource to be intialized after loading.
		 */
		virtual void Initialize() override;

		void UpdateAxis(AxisInputAction upate);

		std::vector<AxisInputAction> PollAxes();

		AxisInputAction PollAxis(const utils::Name& axisName);


		InputAction GetActionMapping(const KeyboardInput& input) const;
		InputAction GetActionMapping(const MouseInput& input) const;
		InputAction GetActionMapping(const GamepadInput& input) const;

		/**
		 * Dummy function to allow template deduction. DO NOT CALL
		 */
		InputAction GetActionMapping(const AxisInput& input) const;

		AxisInputAction GetAxisMapping(const KeyboardInput& input) const;
		AxisInputAction GetAxisMapping(const MouseInput& input) const;
		AxisInputAction GetAxisMapping(const GamepadInput& input) const;
		AxisInputAction GetAxisMapping(const AxisInput& input) const;

		bool IsBound(const KeyboardInput& input) const;
		bool IsBound(const MouseInput& input) const;
		bool IsBound(const GamepadInput& input) const;
		bool IsBound(const AxisInput& input) const;

		bool IsBoundToAction(const KeyboardInput& input) const;
		bool IsBoundToAction(const MouseInput& input) const;
		bool IsBoundToAction(const GamepadInput& input) const;
		bool IsBoundToAction(const AxisInput& input) const;

		bool IsBoundToAxis(const KeyboardInput& input) const;
		bool IsBoundToAxis(const MouseInput& input) const;
		bool IsBoundToAxis(const GamepadInput& input) const;
		bool IsBoundToAxis(const AxisInput& input) const;

	private:
		
		void LoadActionMappings();
		void LoadAxisMappings();

		std::unordered_map<utils::Name, std::shared_ptr<InputAxis>> InputAxes;

		/** Bindings for buttons to Actions */
		std::unordered_map<KeyboardButton, utils::Name> KeyboardActionBindings;
		std::unordered_map<MouseButton, utils::Name> MouseActionBindings;
		std::unordered_map<GamepadButton, utils::Name> GamepadActionBindings;

		/** Bindings for buttons to Axes */
		std::unordered_map<KeyboardButton, std::pair<utils::Name, float>> KeyboardAxisBindings;
		std::unordered_map<MouseButton, std::pair<utils::Name, float>> MouseAxisBindings;
		std::unordered_map<GamepadButton, std::pair<utils::Name, float>> GamepadAxisBindings;

		/** Bindings for analog axes to AxisActions */
		std::unordered_map<RawAxisType, std::pair<utils::Name, float>> AnalogAxisBindings;
	};


}


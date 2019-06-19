#pragma once
//STD headers
#include <functional>

//Library headers

//Coati headers
#include "GenericInput.h"
#include "EngineUtilities.h"

namespace EngineCore {
	enum class GamepadButton : unsigned {

	};

	class GamepadInput : public GenericInput {
	
	public:
		//tors
		GamepadInput(GamepadButton button, ButtonState state);
		GamepadInput(GamepadButton button, ButtonState state, EngineUtilities::GameTime time);
		~GamepadInput();

	public:

		GamepadButton GetGamepadButton() const;
		std::size_t Hash() const override;
	};

	using GamepadInputPtr = std::shared_ptr<GamepadInput>;
}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<EngineCore::GamepadInput> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const EngineCore::GamepadInput& t) const {
			return t.Hash();
		}

	};
}
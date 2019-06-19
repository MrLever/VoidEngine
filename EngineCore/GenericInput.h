#pragma once
//STD Headers
#include <cstddef>
#include <memory>

//Library Headers

//Coati Headers
#include "EngineUtilities.h"

namespace EngineCore {
	enum class ButtonState : unsigned {
		Released = 0,
		Pressed = 1,
		Held = 2,
		Any = 4
	};

	class GenericInput {

	protected:
		unsigned Button;
		ButtonState State;
		EngineUtilities::GameTime TimeStamp;

	public:
		GenericInput(unsigned button, ButtonState state, EngineUtilities::GameTime time);
		~GenericInput() = default;

		virtual bool operator==(const GenericInput& other) const;

	public:
		unsigned GetButton() const;
		ButtonState GetButtonState() const;
		EngineUtilities::GameTime GetTimeStamp() const;

		virtual std::size_t Hash() const;
	};

	using GenericInputPtr = std::shared_ptr<GenericInput>;
}
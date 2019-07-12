#pragma once
//STD Headers
#include <cstddef>
#include <memory>

//Library Headers

//Coati Headers
#include "EngineUtilities.h"
#include "TimeUtils.h"

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
		EngineUtils::GameTime TimeStamp;

	public:
		GenericInput(unsigned button, ButtonState state, EngineUtils::GameTime time);
		~GenericInput() = default;

		virtual bool operator==(const GenericInput& other) const;

	public:

		template<typename T>
		T GetButton() const;
		ButtonState GetButtonState() const;
		EngineUtils::GameTime GetTimeStamp() const;

		virtual std::size_t Hash() const;
	};

	template<typename T>
	T GenericInput::GetButton() const {
		return static_cast<T>(Button);
	}


	using GenericInputPtr = std::shared_ptr<GenericInput>;
}
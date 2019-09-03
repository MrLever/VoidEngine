#pragma once
//STD Headers
#include <queue>

//Library Headers

//Coati Headers
#include "InputInterface.h"
#include "KeyboardInput.h"

namespace EngineCore {

	/**
	 * @class KeyboardInterface
	 */
	class KeyboardInterface : public InputInterface<KeyboardInput> {
	public:
		KeyboardInterface() = default;
		~KeyboardInterface() = default;
	};

}
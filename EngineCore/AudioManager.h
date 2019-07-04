#pragma once

//STD Headers
#include <chrono>
#include <memory>

//Library Headers

//Coati Headers
#include "MessageBusNode.h"

namespace EngineCore {

	class AudioManager {
	private:
		//Private class members

	public:
		//CTORS
		AudioManager(std::shared_ptr<MessageBus> GameMessageBus);
		~AudioManager() = default;

	private:
		//Private member functions

	protected:


	public:
		//Public Member functions

	};

}
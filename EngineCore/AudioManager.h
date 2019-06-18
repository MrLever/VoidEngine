#pragma once

//STD Headers
#include <chrono>
#include <memory>

//Library Headers

//Coati Headers
#include "MessageBusNode.h"

namespace EngineCore {

	//Forward Class declarations
	class MessageBus;


	class AudioManager : MessageBusNode {
	private:
		//Private class members

	public:
		//CTORS
		AudioManager(std::shared_ptr<MessageBus> GameMessageBus);
		~AudioManager() = default;

	private:
		//Private member functions

	protected:
		void RegisterEvents() override;

	public:
		//Public Member functions
		void ReceiveMessage(const Message &message) override;

	};

}
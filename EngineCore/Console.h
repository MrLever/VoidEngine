#pragma once

//STD Headers

//Library Headers

//Coati Headers
#include "MessageBusNode.h"


namespace EngineCore {

	class Console : MessageBusNode {

	private:
		//Private class members
		bool OutputActive;

	public:
		//CTORS
		Console(std::shared_ptr<MessageBus> Bus);
		~Console() = default;

	private:
		void ToggleOutputActive();
		void RegisterEvents() override;
		void RegisterReciever() override;

	public:
		void ReceiveMessage(const Message &message) override;
	};

}
#pragma once
//STD Headers
#include <chrono>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>

//Library Headers

//Coati Headers
#include "Message.h"
#include "EventTable.h"

namespace EngineCore {

	//Forward Class declarations
	class MessageBus;


	class MessageBusNode {
	private:
		//Private Class Members


	protected:
		//Protected Class Members

		std::shared_ptr<MessageBus> GameMessageBus;

		//Binds messages to functions
		EventTable Events;

	public:
		//CTORS
		MessageBusNode(std::shared_ptr<MessageBus> GameMessageBus);
		~MessageBusNode();

	private:
		//Privatate Member Functions

	protected:
		//Protected Member Functions

		virtual void RegisterReciever();
		virtual void UnregisterReciever();

		virtual void RegisterEvents() = 0;

		void PublishMessage(std::string message, MessageType type);
		void PublishMessage(Message message);

	public:
		//Public Member Functions
		std::function<void(Message)> GetMessageReceiveFunction();
		virtual void ReceiveMessage(Message message) = 0;

	};

}
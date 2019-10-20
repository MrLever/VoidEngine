#pragma once

//STD Headers

//Library Headers

//Coati Headers
#include "MessageBusNode.h"

namespace core {

	enum class LogLevel {
		INFO,
		DEBUG,
		WARNING
	};

	class Console : MessageBusNode {
	public:
		/**
		 * Constructor
		 */
		Console(std::shared_ptr<MessageBus> Bus);
		
		/**
		 * Destructor
		 */
		~Console() = default;

		/**
		 * Overrided function that defines how the Console responds to messages
		 * @param message The incomming message
		 */
		void ReceiveMessage(const Message &message) override;

		/**
		 * Allows caller to log message to message bus
		 * @param message The message to log
		 * @param level The log's level
		 */
		void Log(const std::string message, LogLevel level);
	
	private:
		/**
		 * Toggles whether the Console writes to stdout
		 */
		void ToggleOutputActive();

		/**
		 * Registers events that the console will respond to
		 */
		void RegisterEvents() override;

		/**
		 * Registers the console with the Game's active message bus
		 */
		void RegisterReciever() override;

		/** Flag that determines whether the console outputs to stdout*/
		bool OutputActive;
	};

}
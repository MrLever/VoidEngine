#pragma once

//STD Headers

//Library Headers

//Coati Headers
#include "MessageBusNode.h"


namespace EngineCore {

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